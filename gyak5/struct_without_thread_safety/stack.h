#ifndef STACK.h
#define STACK.h

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct stack {
    Node *top;
} Stack;

void initialize(Stack *s) ;

void push(Stack *s, int value) ;

int pop(Stack *s) ;

void free_stack(Stack *s) ;

#endif