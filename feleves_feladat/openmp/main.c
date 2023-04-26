#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

struct Point
{
    double x;
    double y;
} typedef Point;

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
    srand(time(NULL));
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

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    clock_t start, end;
    int n = 500000;
    start = clock();
    double pi = linear_pi(n);
    end = clock();
    printf("pi: %f\n", pi);
    printf("time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}
