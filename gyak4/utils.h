#include <time.h>
#include <stdlib.h>

int* generateRandomIntArray(int size, int min, int max){
    time_t t;
    int* array = (int*)malloc(size * sizeof(int));
    srand((unsigned) time(&t));
    for(int i = 0; i < size; i++){
        array[i] = rand() % (max - min + 1) + min;
    }
    return array;
};

double* generateRandomDoubleArray(int size, int min, int max){
    time_t t;
    double* array = (double*)malloc(size * sizeof(double));
    srand((unsigned) time(&t));
    for(int i = 0; i < size; i++){
        array[i] = (double)rand() / (double)RAND_MAX * (max - min) + min;
    }
    return array;
};