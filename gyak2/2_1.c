#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int sumArray(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return sum;
}

int minArray(int array[], int size)
{
    int min = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

int maxArray(int array[], int size)
{
    int max = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int sumArrayRec(int array[], int size)
{
    if (size == 1)
    {
        return array[0];
    }
    return array[size - 1] + sumArrayRec(array, size - 1);
}

int minArrayRec(int array[], int size)
{
    if (size == 1)
    {
        return array[0];
    }
    int min = minArrayRec(array, size - 1);
    if (array[size - 1] < min)
    {
        min = array[size - 1];
    }
    return min;
}

int maxArrayRec(int array[], int size)
{
    if (size == 1)
    {
        return array[0];
    }
    int max = maxArrayRec(array, size - 1);
    if (array[size - 1] > max)
    {
        max = array[size - 1];
    }
    return max;
}

double runTime(int array[], int size, int (*func)(int[], int))
{
    clock_t start, end;
    start = clock();
    func(array, size);
    end = clock();
    printf("start: %f, end: %f\n", start, end);
    return (double)(end - start) / (double)(CLOCKS_PER_SEC) ;
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    int array[100000];
    for (int i = 0; i < 100000; i++)
    {
        array[i] = rand() % 1000;
    }
    printf("1:%d, 10:%d, 100:%d\n", array[0], array[9], array[99]);
    int size = sizeof(array) / sizeof(int);
    start = clock();
    printf("Sum of array: %d\n", sumArray(array, size));
    printf("Min of array: %d\n", minArray(array, size));
    printf("Max of array: %d\n", maxArray(array, size));
    printf("Rec sum of array: %d\n", sumArrayRec(array, size));
    printf("Rec min of array: %d\n", minArrayRec(array, size));
    printf("Rec max of array: %d\n", maxArrayRec(array, size));
    printf("Run time of sumArray: %f\n", runTime(array, size, sumArray));
    printf("Run time of minArray: %f\n", runTime(array, size, minArray));
    printf("Run time of maxArray: %f\n", runTime(array, size, maxArray));
    printf("Run time of sumArrayRec: %f\n", runTime(array, size, sumArrayRec));
    printf("Run time of minArrayRec: %f\n", runTime(array, size, minArrayRec));
    printf("Run time of maxArrayRec: %f\n", runTime(array, size, maxArrayRec));

    end = clock();
    printf("Time spent: %f\n", (double)(end - start) / (double)(CLOCKS_PER_SEC) );
    return 0;
}
