#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct linked_list {
    Node *head;
    Node *tail;
} LinkedList;

void initialize(LinkedList *ll) ;

void insert(LinkedList *ll, int value) ;

void free_list(LinkedList *ll) ;

#endif