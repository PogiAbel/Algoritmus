#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mystruct.h"

void initialize_array(DynamicArray *da) {
    da->size = 0;
    da->capacity = 10;
    da->array = (int *) malloc(da->capacity * sizeof(int));
    pthread_mutex_init(&da->lock, NULL);
}

void insert_array(DynamicArray *da, int value) {
    pthread_mutex_lock(&da->lock);
    if (da->size == da->capacity) {
        da->capacity *= 2;
        da->array = (int *) realloc(da->array, da->capacity * sizeof(int));
    }
    da->array[da->size++] = value;
    pthread_mutex_unlock(&da->lock);
}


void initialize_linked_list(LinkedList *ll) {
    ll->head = NULL;
    ll->tail = NULL;
    pthread_mutex_init(&ll->lock, NULL);
}

void insert_list(LinkedList *ll, int value) {
    pthread_mutex_lock(&ll->lock);
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (ll->tail == NULL) {
        ll->head = new_node;
        ll->tail = new_node;
    } else {
        ll->tail->next = new_node;
        ll->tail = new_node;
    }
    pthread_mutex_unlock(&ll->lock);
}


void initialize_queue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    pthread_mutex_init(&q->lock, NULL);
}

void enqueue(Queue *q, int value) {
    pthread_mutex_lock(&q->lock);
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
    pthread_mutex_unlock(&q->lock);
}

int dequeue(Queue *q) {
    pthread_mutex_lock(&q->lock);
    if (q->front == NULL) {
        pthread_mutex_unlock(&q->lock);
        return -1; // error, queue is empty
    }
    Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    pthread_mutex_unlock(&q->lock);
    return value;
}

void initialize_stack(Stack *s) {
    s->top = NULL;
    pthread_mutex_init(&s->lock, NULL);
}

void push(Stack *s, int value) {
    pthread_mutex_lock(&s->lock);
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = s->top;
    s->top = new_node;
    pthread_mutex_unlock(&s->lock);
}

int pop(Stack *s) {
    pthread_mutex_lock(&s->lock);
    if (s->top == NULL) {
        pthread_mutex_unlock(&s->lock);
        return -1; // error, stack is empty
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    pthread_mutex_unlock(&s->lock);
    return value;
}