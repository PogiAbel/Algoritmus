#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
    Stack s;
    initialize(&s);
    push(&s, 4);
    push(&s, 10);
    int last = pop(&s);
    printf("%d", last);
    last = pop(&s);
    printf("%d", last);
    return 0;
}
