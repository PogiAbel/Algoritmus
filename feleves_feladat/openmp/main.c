#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

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

Result linear(int n){
    // calculate pi with linear
    clock_t start, end;
    Result result;

    start = clock();
    double liner_pi = linear_pi(n);
    end = clock();
    return (Result){liner_pi, (double)(end - start) / CLOCKS_PER_SEC};
}

Result parallel(int n, int thread_count){
    // calculate pi with parallel
    clock_t start, end;
    Result result;

    start = clock();
    double pi_par = parallel_pi(n, thread_count);
    end = clock();
    return (Result){pi_par, (double)(end - start) / CLOCKS_PER_SEC};
}

int main(int argc, char const *argv[])
{
    // init values
    srand(time(NULL));
    clock_t start, end;
    int n = 500000;

    return 0;
}
