#include "queue.h"
#include <stdlib.h>

void initialize(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Queue *q, int value) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = new_node;
        q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

int dequeue(Queue *q) {
    if (q->front == NULL) {
        return -1; // error, queue is empty
    }
    Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

void free_queue(Queue *q) {
    Node *current = q->front;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}