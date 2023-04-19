#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int* random_intiger(int* array,int min, int max,int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        array[i]=rand() % (max - min + 1) + min;
    }
    
    return array;
}

void print_array(int* array,int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
}

int* insert_sorting_algorithm_return(int* array,int size){
    int i,j,key;
    int *y = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        y[i] = array[i];
    }
    for ( i = 1; i < size; i++)
    {
        key = y[i];
        j = i-1;
        while (j >= 0 && y[j] > key)
        {
            y[j+1] = y[j];
            j--;
        }
        y[j+1] = key;
    }
    return y;
}

void insert_sorting_algorithm(int* array, int size){
    int i,j,key;
    int *y = array;
    for (int i = 0; i < size; i++)
    {
        y[i] = array[i];
    }
    for ( i = 1; i < size; i++)
    {
        key = y[i];
        j = i-1;
        while (j >= 0 && y[j] > key)
        {
            y[j+1] = y[j];
            j--;
        }
        y[j+1] = key;
    }
}

void sort_number(int *array,int size){
    int key,j;
    key = array[size-1];
    j = size-2;
    while (j >= 0 && array[j] > key)
    {
        array[j+1] = array[j];
        j--;
    }
    array[j+1] = key;
}

struct arg_struct{
    int *array;
    int size;
};

void* sorting_single(void* arg){
    struct arg_struct *args = arg;
    int *array = args->array;
    int size = args->size;
    sort_number(array,size);
    pthread_exit(NULL);
}

void* sort_full(void* arg){
    struct arg_struct *args = arg;
    int *array = args->array;
    int size = args->size;
    insert_sorting_algorithm(array,size);
    pthread_exit(NULL);
}

int* copy_array(int* array,int size){
    int *y = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        y[i] = array[i];
    }
    return y;
}

int check_array(int* array1,int* array2,int size){
    for (int i = 0; i < size; i++)
    {
        if (array1[i] != array2[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n = 10000;
    int n_threads = n;
    clock_t start, end;
    int *x = (int*)malloc(n * sizeof(int));
    int *y = (int*)malloc(n * sizeof(int));

    x = random_intiger(x,0,100,n);
    y = copy_array(x,n);
    check_array(x,y,n)? printf("The arrays are the same\n"):printf("The arrays are not the same\n");

    pthread_t threads[n_threads];
    struct arg_struct args;
    args.array = x;
    args.size = n;

    start = clock();
    insert_sorting_algorithm(y,n);
    end = clock();
    double time1 = ((double)(end - start))/ CLOCKS_PER_SEC;
    printf("Linear time : %f\n", time1);

    for (int i = 0; i < n_threads; i++)
    {
        pthread_create(&threads[i],NULL,sorting_single,&args);
        sleep(0.01);
    }

    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(threads[i],NULL);
    }
    
    end = clock();
    double time = ((double)(end - start))/ CLOCKS_PER_SEC;
    printf("Parallel time : %f\n", time);

    check_array(x,y,n)? printf("The arrays are the same\n"):printf("The arrays are not the same\n");

    return 0;
}
