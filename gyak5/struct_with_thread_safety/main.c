#include <stdio.h>
#include <stdlib.h>
#include "mystruct.h"

int search_list(LinkedList *ll, int value) {
    pthread_mutex_lock(&ll->lock);
    Node *current = ll->head;
    while (current != NULL) {
        if (current->data == value) {
            pthread_mutex_unlock(&ll->lock);
            return 1;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&ll->lock);
    return 0;
}

void found_inlist(){
    printf("Found in list");
}

void not_found_inlist(){
    printf("Not found in list");
}

void search_func(LinkedList *ll, int value, void (*func)(), void (*func2)()){
    if(search_list(ll, value)){
        func();
    }else{
        func2();
    }
}

int main(int argc, char const *argv[])
{
    LinkedList ll;
    initialize_linked_list(&ll);
    insert_list(&ll, 10);
    insert_list(&ll, 20);
    insert_list(&ll, 30);
    insert_list(&ll, 40);

    search_func(&ll, 23, found_inlist, not_found_inlist);

    return 0;
}
