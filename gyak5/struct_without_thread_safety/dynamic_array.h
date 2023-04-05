#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct dynamic_array {
    int *array;
    int size;
    int capacity;
} DynamicArray;

void initialize(DynamicArray *da);

void insert(DynamicArray *da, int value) ;

void free_array(DynamicArray *da) ;

#endif