#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

struct Point
{
    double x;
    double y;
} typedef Point;

struct Result
{
    double pi;
    double time;
} typedef Result;

Point random_point(){
    // gives random point between 0 and 1
    Point p;
    p.x = (double)rand() / RAND_MAX;
    p.y = (double)rand() / RAND_MAX;
    return  p;
    
}

int is_in_circle(Point p){
    // checks if point is in circle
    return (p.x * p.x + p.y * p.y) <= 1;
}

double linear_pi(int n){
    // calculates pi with linear method
    int in_circle = 0;
    int out_circle = 0;
    for (int i = 0; i < n; i++)
    {
        Point p = random_point();
        if(is_in_circle(p)){
            in_circle++;
        } else {
            out_circle++;
        }
    }
    return (double)in_circle / (double)n * 4;
}

double parallel_pi(int n, int thread_count){
    // calculates pi with parallel method
    int in_circle = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    int group_size = n / thread_count;

    #pragma omp parallel for
    for (int i = 0; i < thread_count; i++)
    {
        int local_count = 0;
        for (int i = 0; i < group_size; i++)
        {
            Point p = random_point();
            if(is_in_circle(p)){
                local_count++;
            }
        }
        omp_set_lock(&lock);
        in_circle += local_count;
        omp_unset_lock(&lock);

    }
    return (double)in_circle / (double)n * 4;
}

double pi_calculation_3d(int n){
    // calculates pi with 3d method
    int in_circle = 0;
    int out_circle = 0;
    for (int i = 0; i < n; i++)
    {
        Point p = random_point();
        if(is_in_circle(p)){
            in_circle++;
        } else {
            out_circle++;
        }
    }
    return (double)in_circle / (double)n * 4;
}

double pi_calculation_3d_parallel(int n, int thread_count){
    // calculates pi with 3d parallel method
    int in_circle = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    int group_size = n / thread_count;

    #pragma omp parallel for
    for (int i = 0; i < thread_count; i++)
    {
        int local_count = 0;
        for (int i = 0; i < group_size; i++)
        {
            Point p = random_point();
            if(is_in_circle(p)){
                local_count++;
            }
        }
        omp_set_lock(&lock);
        in_circle += local_count;
        omp_unset_lock(&lock);

    }
    return (double)in_circle / (double)n * 4;
}

Result linear(int n){
    // calculation done with linear
    clock_t start, end;
    Result result;

    start = clock();
    double liner_pi = linear_pi(n);
    end = clock();
    return (Result){liner_pi, (double)(end - start) / CLOCKS_PER_SEC};
}

Result parallel(int n, int thread_count){
    // calculation done with parallel
    clock_t start, end;
    Result result;

    start = clock();
    double pi_par = parallel_pi(n, thread_count);
    end = clock();
    return (Result){pi_par, (double)(end - start) / CLOCKS_PER_SEC};
}

Result linear_3d(int n){
    // calculation done with linear in 3d
    clock_t start, end;
    Result result;

    start = clock();
    double liner_pi = pi_calculation_3d(n);
    end = clock();
    return (Result){liner_pi, (double)(end - start) / CLOCKS_PER_SEC};
}

Result parallel_3d(int n, int thread_count){
    // calculation done with parallel in 3d
    clock_t start, end;
    Result result;

    start = clock();
    double pi_par = pi_calculation_3d_parallel(n, thread_count);
    end = clock();
    return (Result){pi_par, (double)(end - start) / CLOCKS_PER_SEC};
}

void write_result_to_file(){
    double result_matrix[22][6];
    result_matrix[0][0] = 0;
    int row, col = 1;

    FILE *fp;
    fp = fopen("./statics/result_3d_2.txt", "w");

    for (int n = 100000000; n <= 500000000; n+=100000000)
    {
        row = 1;

        Result linear_result = linear_3d(n);

        result_matrix[0][col] = n;
        result_matrix[row][0] = 1;
        result_matrix[row][col] = linear_result.time;

        for (int thread_count = 2; thread_count <= 20; thread_count+=2)
        {
            row ++; 
            Result parallel_result = parallel_3d(n, thread_count);
            result_matrix[row][col] = parallel_result.time;
            result_matrix[row][0] = thread_count;
        }

        col ++;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fprintf(fp, "%f, ", result_matrix[i][j]);
        }
        fprintf(fp, "\n");
        
    }
    

    fclose(fp);
    printf("Done\n");
}

void pi_estimation_limit(){
    double pi_estimation = 0;
    double limit = 0.000001;
    int in_circle = 0;
    int all_count = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);

    while (fabs(pi_estimation-PI) > limit)
    {

        #pragma omp parallel for
        for (int i = 0; i < 10; i++)
        {
            int local_count = 0;
            for (int j = 0; j < 500; j++)
            {
                Point p = random_point();
                if(is_in_circle(p)){
                    local_count++;
                }
            }
            omp_set_lock(&lock);
            all_count += 500;
            in_circle += local_count;
            omp_unset_lock(&lock);

        }

        pi_estimation =  (double)in_circle / (double)all_count * 4;
    }
    printf("Estimation limit: %f\n", limit);    
    printf("Total count: %d\n", all_count);    
    
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    // clock_t start, end;
    // start = clock();
    // pi_estimation_limit();
    // end = clock();
    // printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    write_result_to_file();

    return 0;
}
