import threading
import random
import math
import time

def sum(num:list):
    sum = 0
    for i in num:
        sum += i
    return sum

def rec_sum(num:list):
    # Max recursion depth exceeded so i didnt use it
    if len(num) == 1:
        return num[0]
    else:
        return num[0] + rec_sum(num[1:])

def random_array():
    arr = []
    for i in range(ARRAY_SIZE):
        arr.append(random.randint(1,1000))
    return arr

def thread_sum(num:list):
    global RESULT
    RESULT += sum(num)

def main():
    arr = random_array()
    little_arr = []
    db =math.ceil(ARRAY_SIZE / THREADS)
    threads = []
    for i in range(db):
        little_arr.append(arr[i*THREADS:(i+1)*THREADS])
    start = time.time()
    for i in range(db):
        threads.append(threading.Thread(target=thread_sum, args=(little_arr[i],)))
        threads[i].start()
    for x in threads:
        x.join()
    end = time.time()
    # print(f"Thread numbers: {THREADS},thread sum: {RESULT}, sec: {end-start}")
    # print(f"Simple sum: {summ}, sec: {end-start}")
    with open("result.txt", "a") as f:
        f.write(f"{THREADS},{ARRAY_SIZE},{RESULT},{end-start}\n")
        
if __name__ == "__main__":
    ARRAY_SIZE = 10000
    THREADS = 1
    RESULT = 0

    with open("result.txt", "w") as f:
        f.write(f"Thread numbers, array size,thread sum, sec\n")
    
    for i in range(1,6):
        ARRAY_SIZE = i*10000
        for i in range(5,10):
            THREADS = i
            main()