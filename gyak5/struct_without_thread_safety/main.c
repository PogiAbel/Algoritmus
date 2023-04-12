#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <omp.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    Stack s;
    initialize(&s);
    int top = 0;
    push(&s, 10);
    #pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        push(&s, i);
        top = pop(&s);
        printf("%d ", top);
    }
    return 0;
}
