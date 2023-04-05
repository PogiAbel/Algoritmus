#include "linked_list.h"
#include <stdlib.h>

void initialize(LinkedList *ll) {
    ll->head = NULL;
    ll->tail = NULL;
}

void insert(LinkedList *ll, int value) {
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
}

void free_list(LinkedList *ll) {
    Node *current = ll->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}