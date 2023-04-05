#include "stack.h"
#include <stdlib.h>

void initialize(Stack *s) {
    s->top = NULL;
}

void push(Stack *s, int value) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = s->top;
    s->top = new_node;
}

int pop(Stack *s) {
    if (s->top == NULL) {
        return -1; // error, stack is empty
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

void free_stack(Stack *s) {
    Node *current = s->top;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}
