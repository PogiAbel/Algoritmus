#include <stdio.h>
#include <windows.h>
#include <time.h>

int main() {
    time_t t;
    time(&t);
    printf("Hello World! %s", ctime(&t));
    Sleep(2000);
    printf("Hello World! %s", ctime(&t));

    return 0;
}