#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

int main(int argc, char const *argv[])
{
    Stack s;
    initialize_stack(&s);
    push(&s, 50);
    push(&s, 22);
    int last = pop(&s);
    printf("%d", last);
    last = pop(&s);
    printf("%d", last);
    return 0;
}
