#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;

    srand((unsigned) time(&t));
    int first = rand()%1001 + 500;
    for (size_t i = 0; i < 10; i++)
    {
    printf("Random number: %d\n" , rand()%1001 + 500);    
    }
    

    return 0;
}