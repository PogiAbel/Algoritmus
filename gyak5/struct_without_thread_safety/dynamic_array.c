#include "dynamic_array.h"
#include <stdlib.h>

void initialize(DynamicArray *da) {
    da->size = 0;
    da->capacity = 10;
    da->array = (int *) malloc(da->capacity * sizeof(int));
}

void insert(DynamicArray *da, int value) {
    if (da->size == da->capacity) {
        da->capacity *= 2;
        da->array = (int *) realloc(da->array, da->capacity * sizeof(int));
    }
    da->array[da->size++] = value;
}

void free_array(DynamicArray *da) {
    free(da->array);
}