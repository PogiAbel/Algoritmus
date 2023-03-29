#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;
    clock_t begin, end;

    srand((unsigned) time(&t));
    int first = rand()%100;
    int secound = rand()%100;
    int correct = first + secound;
    int answer;
    printf("%d + %d = ",first,secound);
    begin = clock();
    scanf("%d", &answer);
    end = clock();
    if(answer == correct){
    printf("Thats correct\n");
    } else {
    printf("Thats incorrect\n");
    }
    printf("Time spent: %f",(double) (end-begin));
    

    return 0;
}