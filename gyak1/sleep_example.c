#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    clock_t begin, end;
    begin = clock();
    printf("start\n");
    sleep(5); // Sleep for 5 milliseconds
    printf("end\n");
    end = clock();
    double time_spent = (double) (end-begin);
    printf("Time spent: %f", time_spent);
    return 0;
}