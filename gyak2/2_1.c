#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


int sumArray(int array[], int i)
{
    int sum = 0;
    for (int i = 0; i < i; i++)
    {   
        sum += array[i];
    }
    return sum;
}

int minArray(int array[], int i)
{
    int min = array[0];
    for (int i = 0; i < i; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }

    return min;
}

int maxArray(int array[], int i)
{
    int max = array[0];
    for (int i = 0; i < i; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}

int sumArrayRec(int array[], int i)
{
    if (i == 1)
    {
        return array[0];
    }
    return array[i - 1] + sumArrayRec(array, i - 1);
}

int minArrayRec(int array[], int i)
{
    if (i == 1)
    {
        return array[0];
    }
    int min = minArrayRec(array, i - 1);
    if (array[i - 1] < min)
    {
        min = array[i - 1];
    }
    return min;
}

int maxArrayRec(int array[], int i)
{
    if (i == 1)
    {
        return array[0];
    }
    int max = maxArrayRec(array, i - 1);
    if (array[i - 1] > max)
    {
        max = array[i - 1];
    }
    return max;
}

double runTime(int* array, int i, int (*func)(int[], int))
{
    // get the run time of the function 
    clock_t start, end;
    start = clock();
    int result =    func(array, i);
    end = clock();
    printf("Start: %f, End: %f\n", (double)start, (double)end);
    double time = ((double)(end - start))/ CLOCKS_PER_SEC;
     printf("Time : %f\n", time);
    return time ;

}

int * getArray(int n){
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 1000;
    }
    return array;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    fp = fopen("gyak2_1.txt", "w");
    fprintf(fp, "n, sum, min, max, sumRec, minRec, maxRec\n");

    for (int i = 1000; i <= 10000; i+=1000)
    {
        int * array;
        array = getArray(i);
        double sumTime = runTime(array, i, sumArray);
        double minTime = runTime(array, i, minArray);
        double maxTime = runTime(array, i, maxArray);
        double sumRecTime = runTime(array, i, sumArrayRec);
        double minRecTime = runTime(array, i, minArrayRec);
        double maxRecTime = runTime(array, i, maxArrayRec);
        fprintf(fp, "%d, %f, %f, %f, %f ,%f, %f\n", i, sumTime, minTime, maxTime, sumRecTime, minRecTime, maxRecTime);
        // printf( "%d, %f, %f, %f, %f ,%f, %f\n", i, sumTime, minTime, maxTime, sumRecTime, minRecTime, maxRecTime);
        free(array);
    }
    fclose(fp);
    return 0;
}
