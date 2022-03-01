#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t now;
    time(&now);
    printf("Today is %s", ctime(&now));
    
    printf("Most");
    sleep(5);
    printf("\nSleep utan");
    printf("\nToday is %s", ctime(&now));
    sleep(5);


    return 0;
}