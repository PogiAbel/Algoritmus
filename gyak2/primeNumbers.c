#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int primeNumbers(int n)
{
    int i, j;
    int prime = 0;
    for (i = 2; i < n; i++)
    {
        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                break;
            }
        }
        if (i == j)
        {
            prime++;
        }
    }
    return prime;
}

int main(int argc, char const *argv[])
{
    clock_t start, end;

    FILE *fpt;
    fpt = fopen("./primeNumbers.txt", "w");

    if (fpt == NULL)
    {
        printf("Error!");
        return 1;
    }

    for (int n = 1000; n <= 20000; n += 1000)
    {
        start = clock();
        primeNumbers(n);
        end = clock();
        fprintf(fpt, "%d, %f\n", n, (double)(end - start));
    }

    fclose(fpt);

    return 0;
}
