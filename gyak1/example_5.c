#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;
    int min, max, n, random;

    srand((unsigned) time(&t));
    printf("Random number minimum: ");
    scanf("%d",&min);
    printf("Random number maximum: ");
    scanf("%d",&max);
    printf("Random numbers count: ");
    scanf("%d",&n);
  
    
    FILE *ptr;
    ptr = fopen("./random_numbers.txt", "w");
    if(ptr == NULL){
        printf("Error!");
        return 1;
    }

    for (size_t i = 0; i < n; i++)
    {
        random = (rand() % (max-min+1) ) + min;
        fprintf(ptr,"%d\n", random);
        printf("Random number: %d\n" ,random  );
    }

    fclose(ptr);

    return 0;
}