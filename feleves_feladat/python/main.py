import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
from PIL import Image
import concurrent.futures
from multiprocessing import Pool
import time
import math
import sys

img_name = ''
try:
    img_name = sys.argv[1]
except:
    img_name = "me.jpg"
img_path = f'input/{img_name}'
num_regions = 50

def demonstrate():
    img = cv.imread(img_path, 0)
    edges = cv.Canny(img,100,200)

    plt.subplot(121),plt.imshow(img,cmap = 'gray')
    plt.title('Original Image'), plt.xticks([]), plt.yticks([])
    plt.subplot(122),plt.imshow(edges,cmap = 'gray')
    plt.title('Edge Image'), plt.xticks([]), plt.yticks([])

    plt.show()
    
def show_result(img):
    original = cv.imread(img_path)
    start_time = time.time()
    edges = Canny_detector(original)
    end_time = time.time()
    print("Inbuilt Canny Edge Detection took: " + str(end_time - start_time) + " seconds")
    plt.subplot(131),plt.imshow(original,cmap = 'gray')
    plt.title('Original Image'), plt.xticks([]), plt.yticks([])
    plt.subplot(132),plt.imshow(edges,cmap = 'gray')
    plt.title('Edge Detection'), plt.xticks([]), plt.yticks([])
    plt.subplot(133),plt.imshow(img,cmap = 'gray')
    plt.title('Parallel Edge Image'), plt.xticks([]), plt.yticks([])

    plt.show()
    
def divide_image(img):
    global num_regions
    height, width, _ = img.shape
    optimal = (height * width) /math.gcd(height , width)
    print("Optimal number of regions: " + str(optimal))
    # Calculate the region size based on the number of regions
    region_height = height // num_regions
    region_width = width // num_regions

    regions = []
    for i in range(num_regions):
        for j in range(num_regions):
            # Calculate the region boundaries
            top = i * region_height
            bottom = (i + 1) * region_height
            left = j * region_width
            right = (j + 1) * region_width

            # Extract the region from the image
            region = img[top:bottom, left:right]
            regions.append(region)

    return regions

def rebuild_image(regions):
    region_height, region_width = regions[0].shape
    image_height = region_height * num_regions
    image_width = region_width * num_regions
    
    # Create an empty image with the original size
    rebuilt_image = np.zeros((image_height, image_width), dtype=np.uint8)
    
    # Rebuild the image by placing each region at its corresponding position
    for i in range(num_regions):
        for j in range(num_regions):
            region_index = i * num_regions + j
            region = regions[region_index]
            top = i * region_height
            bottom = top + region_height
            left = j * region_width
            right = left + region_width

            # Account for incomplete regions or overlapping regions
            region_height_actual = min(region_height, image_height - top)
            region_width_actual = min(region_width, image_width - left)

            rebuilt_image[top:top+region_height_actual, left:left+region_width_actual] = region[:region_height_actual, :region_width_actual]
    
    return rebuilt_image

def process_chunk(args):
    chunk, width, height, ang, mag = args

    for i_y, i_x in chunk:
        grad_ang = ang[i_y, i_x]
        grad_ang = abs(grad_ang-180) if abs(grad_ang) > 180 else abs(grad_ang)

        # selecting the neighbours of the target pixel
        # according to the gradient direction
        # In the x-axis direction
        if grad_ang <= 22.5:
            neighb_1_x, neighb_1_y = i_x - 1, i_y
            neighb_2_x, neighb_2_y = i_x + 1, i_y

        # top right (diagonal-1) direction
        elif grad_ang > 22.5 and grad_ang <= (22.5 + 45):
            neighb_1_x, neighb_1_y = i_x - 1, i_y - 1
            neighb_2_x, neighb_2_y = i_x + 1, i_y + 1

        # In y-axis direction
        elif grad_ang > (22.5 + 45) and grad_ang <= (22.5 + 90):
            neighb_1_x, neighb_1_y = i_x, i_y - 1
            neighb_2_x, neighb_2_y = i_x, i_y + 1

        # top left (diagonal-2) direction
        elif grad_ang > (22.5 + 90) and grad_ang <= (22.5 + 135):
            neighb_1_x, neighb_1_y = i_x - 1, i_y + 1
            neighb_2_x, neighb_2_y = i_x + 1, i_y - 1

        # Now it restarts the cycle
        elif grad_ang > (22.5 + 135) and grad_ang <= (22.5 + 180):
            neighb_1_x, neighb_1_y = i_x - 1, i_y
            neighb_2_x, neighb_2_y = i_x + 1, i_y

        # Non-maximum suppression step
        if width > neighb_1_x >= 0 and height > neighb_1_y >= 0:
            if mag[i_y, i_x] < mag[neighb_1_y, neighb_1_x]:
                mag[i_y, i_x] = 0
                return

        if width > neighb_2_x >= 0 and height > neighb_2_y >= 0:
            if mag[i_y, i_x] < mag[neighb_2_y, neighb_2_x]:
                mag[i_y, i_x] = 0
            
def parallel_compute(width, height, ang, mag, chunk_size=2000):
    # Divide the pixels into chunks
    chunks = [(i_y, i_x) for i_y in range(height) for i_x in range(width)]
    chunked_pixels = [chunks[i:i+chunk_size] for i in range(0, len(chunks), chunk_size)]

    # Create a pool of worker processes
    pool = Pool()

    # Process chunks of pixels in parallel
    pool.map(process_chunk, [(chunk, width, height, ang, mag) for chunk in chunked_pixels])

    # Close the pool and wait for the processes to finish
    pool.close()
    pool.join()
    
def paralell_canny(img, weak_th = None, strong_th = None):
    # conversion of image to grayscale
    img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
       
    # Noise reduction step
    img = cv.GaussianBlur(img, (5, 5), 1.4)
       
    # Calculating the gradients
    gx = cv.Sobel(np.float32(img), cv.CV_64F, 1, 0, 3)
    gy = cv.Sobel(np.float32(img), cv.CV_64F, 0, 1, 3)
      
    # Conversion of Cartesian coordinates to polar 
    mag, ang = cv.cartToPolar(gx, gy, angleInDegrees = True)
       
    # setting the minimum and maximum thresholds for double thresholding
    mag_max = np.max(mag)
    if not weak_th:weak_th = mag_max * 0.1
    if not strong_th:strong_th = mag_max * 0.5
      
    # getting the dimensions of the input image  
    height, width = img.shape
    
    parallel_compute(width, height, ang, mag)
    
    weak_ids = np.zeros_like(img)
    strong_ids = np.zeros_like(img)              
    ids = np.zeros_like(img)
       
    # double thresholding step
    for i_x in range(width):
        for i_y in range(height):
              
            grad_mag = mag[i_y, i_x]
              
            if grad_mag<weak_th:
                mag[i_y, i_x]= 0
            elif strong_th>grad_mag>= weak_th:
                ids[i_y, i_x]= 1
            else:
                ids[i_y, i_x]= 2
    # finally returning the magnitude of gradients of edges
    return mag
    

def paralell_canny_old(img):
    regions = divide_image(img)
     # Create a ThreadPoolExecutor with the desired number of threads
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=num_regions)
    
    # Submit the tasks to the executor
    futures = [executor.submit(Canny_detector, chunk) for chunk in regions]
    
    # Retrieve the results as they become available
    edges = [future.result() for future in concurrent.futures.as_completed(futures)]
    
    return edges
    
    
def Canny_detector(img, weak_th = None, strong_th = None):
    # conversion of image to grayscale
    img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
       
    # Noise reduction step
    img = cv.GaussianBlur(img, (5, 5), 1.4)
       
    # Calculating the gradients
    gx = cv.Sobel(np.float32(img), cv.CV_64F, 1, 0, 3)
    gy = cv.Sobel(np.float32(img), cv.CV_64F, 0, 1, 3)
      
    # Conversion of Cartesian coordinates to polar 
    mag, ang = cv.cartToPolar(gx, gy, angleInDegrees = True)
       
    # setting the minimum and maximum thresholds for double thresholding
    mag_max = np.max(mag)
    if not weak_th:weak_th = mag_max * 0.1
    if not strong_th:strong_th = mag_max * 0.5
      
    # getting the dimensions of the input image  
    height, width = img.shape
       
    # Looping through every pixel of the grayscale image
    for i_x in range(width):
        for i_y in range(height):
               
            grad_ang = ang[i_y, i_x]
            grad_ang = abs(grad_ang-180) if abs(grad_ang)>180 else abs(grad_ang)
               
            # selecting the neighbours of the target pixel
            # according to the gradient direction
            # In the x axis direction
            if grad_ang<= 22.5:
                neighb_1_x, neighb_1_y = i_x-1, i_y
                neighb_2_x, neighb_2_y = i_x + 1, i_y
              
            # top right (diagonal-1) direction
            elif grad_ang>22.5 and grad_ang<=(22.5 + 45):
                neighb_1_x, neighb_1_y = i_x-1, i_y-1
                neighb_2_x, neighb_2_y = i_x + 1, i_y + 1
              
            # In y-axis direction
            elif grad_ang>(22.5 + 45) and grad_ang<=(22.5 + 90):
                neighb_1_x, neighb_1_y = i_x, i_y-1
                neighb_2_x, neighb_2_y = i_x, i_y + 1
              
            # top left (diagonal-2) direction
            elif grad_ang>(22.5 + 90) and grad_ang<=(22.5 + 135):
                neighb_1_x, neighb_1_y = i_x-1, i_y + 1
                neighb_2_x, neighb_2_y = i_x + 1, i_y-1
              
            # Now it restarts the cycle
            elif grad_ang>(22.5 + 135) and grad_ang<=(22.5 + 180):
                neighb_1_x, neighb_1_y = i_x-1, i_y
                neighb_2_x, neighb_2_y = i_x + 1, i_y
               
            # Non-maximum suppression step
            if width>neighb_1_x>= 0 and height>neighb_1_y>= 0:
                if mag[i_y, i_x]<mag[neighb_1_y, neighb_1_x]:
                    mag[i_y, i_x]= 0
                    continue
   
            if width>neighb_2_x>= 0 and height>neighb_2_y>= 0:
                if mag[i_y, i_x]<mag[neighb_2_y, neighb_2_x]:
                    mag[i_y, i_x]= 0
   
    weak_ids = np.zeros_like(img)
    strong_ids = np.zeros_like(img)              
    ids = np.zeros_like(img)
       
    # double thresholding step
    for i_x in range(width):
        for i_y in range(height):
              
            grad_mag = mag[i_y, i_x]
              
            if grad_mag<weak_th:
                mag[i_y, i_x]= 0
            elif strong_th>grad_mag>= weak_th:
                ids[i_y, i_x]= 1
            else:
                ids[i_y, i_x]= 2
    # finally returning the magnitude of gradients of edges
    return mag

if __name__ == "__main__":
    img = cv.imread(img_path)
    start_time = time.time()
    edge = paralell_canny(img)
    end_time = time.time()
    print("Parallel Canny Edge Detection took: " + str(end_time - start_time) + " seconds")
    # edge = rebuild_image(edges)
    cv.imwrite("output/parallel_canny_edge.jpg", edge)
    show_result(edge)