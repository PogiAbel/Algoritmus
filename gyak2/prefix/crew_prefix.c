#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct thread_args
{
    int *array;
    int size;
    int *result;
} thread_args;

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* simple_prefix(int *array, int size)
{
    int *result = (int *)malloc(sizeof(int) * size);
    int i = 0;
    int prefix = array[0];
    result[0] = prefix;
    for (i = 1; i < size; i++)
    {
        prefix += array[i];
        result[i] = prefix;
    }
    return result;
}

void *thread_func(void *arg)
{
    thread_args *args = ((thread_args*)arg);
    int size = args->size;
    args->result = simple_prefix(args->array, args->size);
    return NULL;
}

int* paralell_crew_prefix(int *array, int size)
{
    pthread_t threads[2];
    thread_args args[2];
    int *result = (int *)malloc(sizeof(int) * size);
    int left = ceil((double)size/2);
    int right = size-left;
    args[0] = ( thread_args){array, left, NULL};
    args[1] = ( thread_args){array+left, right, NULL};
    printf("Args: %d %d\n", args[0].size, args[0].array[0]);
    // int *left_array = simple_prefix(array, left);
    // int *right_array = simple_prefix(array+left,right);
    for (int i = 0; i < 2; i++)
    {
        int res = pthread_create(&threads[i], NULL, thread_func, (void*)&args[i]);
        if (res != 0)
        {
            printf("Error creating thread\n");
        }
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }
    int *left_array = args[0].result;
    int *right_array = args[1].result;
    for (int i = 0; i < left; i++)
    {
        result[i] = left_array[i];
    }
    for (int i = 0; i < right; i++)
    {
        result[i+left] = right_array[i]+ left_array[left-1];
    }

    return result;
}


int main(int argc, char const *argv[])
{
    int array[] = {1,3,5,7,8,123,34,5};
    int size = sizeof(array) / sizeof(int);
    int *result = paralell_crew_prefix(array, size);
    print_array(result, size);
    print_array(simple_prefix(array,size), size);

    return 0;
}
