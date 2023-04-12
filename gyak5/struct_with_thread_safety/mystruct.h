#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <pthread.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct dynamic_array {
    int *array;
    int size;
    int capacity;
    pthread_mutex_t lock;
} DynamicArray;

typedef struct linked_list {
    Node *head;
    Node *tail;
    pthread_mutex_t lock;
} LinkedList;

typedef struct queue {
    Node *front;
    Node *rear;
    pthread_mutex_t lock;
} Queue;

typedef struct stack {
    Node *top;
    pthread_mutex_t lock;
} Stack;

void initialize_array(DynamicArray *da);
void insert_array(DynamicArray *da, int value);

void initialize_linked_list(LinkedList *ll);
void insert_list(LinkedList *ll, int value);

void initialize_queue(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);

void initialize_stack(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);

#endif
