// 4.gyakorlat 1.feladat

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "utils.h"
#include <time.h>
#include <pthread.h>

double calcTimesInArray(double* array, int start, int end){
    double result = 1;
    for (int i = start; i < end; i++)
    {
        result *= array[i];
    }
    return result;
}

//struct for thread function arguments
typedef struct thread_args
{
    int start;
    int end;
    double* array;
} thread_args;

// thread function
void *threadFunc(void *arg)
{
    thread_args *args = (thread_args *)arg;
    double result = calcTimesInArray(args->array, args->start, args->end);
}

int main(int argc, char const *argv[])
{
    // init variables
    clock_t start, end;
    int size;
    int divison;
    double *array = generateRandomDoubleArray(size,0,10);
    FILE *ptr;
    ptr = fopen("./statics.txt", "w");
    printf("Array size: %d, divison: %d, threads: %d\n", size, divison, size/divison);
    fprintf(ptr, "method, array size, threads, time\n", size, divison, size/divison);

    // increase array size
    for (int i = 100000; i < 800000; i+=100000)  
    {
        size = i;

        // increase divison
        for (int j = 20; j <= 60; j+=20)
        {
            divison = j;

            // linear
            start = clock();
            double res = calcTimesInArray(array, 0, size);
            end = clock();
            printf("Linear time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            fprintf(ptr, "linear, %d, %d, %f\n", size, 1, (double)(end-start)/CLOCKS_PER_SEC);

            // posix threads
            pthread_t threads[size/divison];
            thread_args args[size/divison];
            start = clock();
            for (int k = 0; k < size/divison; k++)
            {
                args[k].start = k*divison;
                args[k].end = k*divison+divison;
                args[k].array = array;
                pthread_create(&threads[k], NULL, threadFunc, (void*)&args[k]);
            }
            for (int k = 0; k < size/divison; k++)
            {
                pthread_join(threads[k], NULL);
            }
            end = clock();
            printf("Posix threads time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            fprintf(ptr, "posix, %d, %d, %f\n", size, size/divison, (double)(end-start)/CLOCKS_PER_SEC);


            // omp parallel
            omp_lock_t writelock;
            omp_init_lock(&writelock);
            res = 1;
            double temp_res = 0;
            start = clock();
            #pragma omp parallel for
            for (int k = 0; k < size; k+=divison)
            {
                temp_res= calcTimesInArray(array, k, k+divison);
                omp_set_lock(&writelock);
                res *= temp_res;
                omp_unset_lock(&writelock);
            }
            end = clock();
            printf("Omp parallel time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            fprintf(ptr, "omp, %d, %d, %f\n", size, size/divison, (double)(end-start)/CLOCKS_PER_SEC);
        }
    }
    fclose(ptr);
    return 0;
}
