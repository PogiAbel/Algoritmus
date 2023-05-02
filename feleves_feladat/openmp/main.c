#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define PI 3.141592

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

int main(int argc, char const *argv[])
{
    // init values
    srand(time(NULL));
    clock_t start, end;

    FILE *fp;
    fp = fopen("result_2d.txt", "w");

    for (int n = 100000; n < 500000; n+=100000)
    {
        fprintf(fp, "%d:\n", n);
        Result linear_result = linear(n);
        fprintf(fp, "Linear: %f, %f\n", linear_result.pi, linear_result.time);
        for (int thread_count = 10; thread_count <= 50; thread_count+=10)
        {
            Result parallel_result = parallel(n, thread_count);
            fprintf(fp, "Parallel: %f, %f\n", parallel_result.pi, parallel_result.time);
        }
        
    }
    fclose(fp);


    return 0;
}
