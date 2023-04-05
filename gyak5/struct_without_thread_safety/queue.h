#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct queue {
    Node *front;
    Node *rear;
} Queue;

void initialize(Queue *q) ;

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

void free_queue(Queue *q);

#endif