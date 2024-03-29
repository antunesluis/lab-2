#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> 

typedef struct _doubly_node {
    int val;
    struct _doubly_node* prev;
    struct _doubly_node* next;
} DoublyNode, Node;


typedef struct _doubly_linked_list {
    Node* begin;
    Node* end;
    size_t size;
} DoublyLinkedList, List;


Node* Node_crete(int val) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->val = val;

    return node;
}

List* List_create() {
    List* L = (List*)calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}

void List_destroy(List** L_ref) {
    List* L = *L_ref;

    Node* p = L->begin;
    Node* aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool List_is_empty(const List* L) {
    return L->size == 0;
}

void List_add_first(List* L, int val) {
    Node* p = Node_crete(val);
    p->next = L->begin;

    if (List_is_empty(L)) {
        L->end = p;
    }
    else {
        L->begin->prev = p;
    }

    // List_is_empty(L) ? (L->end = p) : (L->begin->prev = p); 
    L->begin = p;
    L->size++;

}

void List_add_last(List* L, int val) {
    Node* p = Node_crete(val);
    p->prev = L->end;

    if (List_is_empty(L)) {
        L->begin = p;
    }
    else {
        L->end->next = p;
    }

    // List_is_empty(L) ? (L->begin = p) : (L->end->prev = p);
    L->end = p;
    L->size++;
}

void List_print(const List* L) {
    Node* p = L->begin;

    printf("\nSize: %lu\n", L->size);
    printf("L -> ");

    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L->end = NULL\n");
    }
    else {
        printf("L->end = %d\n", L->end->val);
    }
    puts("");
}

void List_inverted_print(const List* L) {
    Node* p = L->end;

    printf("\nSize: %lu\n", L->size);
    printf("L ->end -> ");

    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->prev;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L->begin = NULL\n");
    }
    else {
        printf("L->begin = %d\n", L->begin->val);
    }
    puts("");
}

void List_remove(List* L, int val) {
    if (List_is_empty(L)) {
        return;
    }

    Node* p = L->begin;

    // caso 1: o elemento está na cabeça da lista
    if (L->begin->val == val) {
        L->begin = p->next;

        // a lista possui apenas um único elemento
        if (L->end == p) {
            L->end = NULL;
        }
        // a lista possui mais de um elemento
        else {
            L->begin->prev = NULL;
        }

        free(p);
        L->size--;
    }
    else {
        p = p->next;

        while (p != NULL) {
            if (p->val == val) {
                p->prev->next = p->next;

                // caso 3: o elemento está no final da lista
                if (L->end == p) {
                    L->end = p->prev;
                }
                // caso 2: o elemento está no meio da lista
                else {
                    p->next->prev = p->prev;
                }

                free(p);
                p = NULL;
                L->size--;
            }
            else {
                p = p->next;
            }
        }
    }
}

void List_remove_first(List* L) {
    if (!List_is_empty(L)) {
        Node* p = L->begin;

        // a lista possui apenas um único elemento
        if (L->begin == L->end) {
            L->begin = NULL;
            L->end = NULL;
        }
        // a lista possui mais do que um elemento
        else {
            L->begin = L->begin->next;
            L->begin->prev = NULL;
        }

        free(p);
        L->size--;
    }
}

void List_remove_last(List* L) {
    if (List_is_empty(L)) {
        Node* p = L->end;

        if (L->begin == L->end) {
            L->begin = NULL;
            L->end = NULL;
        }
        else {
            L->end = L->end->prev;
            L->end->next = NULL;
        }

        free(p);
        L->size--;
    }
}

void remove_at(List* list, size_t position) {
    if (position >= list->size) {
        return;
    }

    Node* current = list->begin;
    Node* previous = NULL;

    for (size_t i = 0; i < position; i++) {
        previous = current;
        current = current->next;
    }

    if (previous != NULL) {
        previous->next = current->next;
    }
    else {
        list->begin = current->next;
    }

    if (current == list->end) {
        list->end = previous;
    }

    free(current);
    list->size--;
}

size_t find_node_position(List* L, int destination) {
    Node* list_begin = L->begin;

    Node* current = list_begin;
    size_t position = 0;

    while (current != NULL && current->val != destination) {
        current = current->next;
        position++;
    }

    return position;
}

void check_empty_list(const List* L, const char* function_name) {
    if (List_is_empty(L)) {
        fprintf(stderr, "ERROR in '%s'\n", function_name);
        fprintf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }
}

size_t List_size(const List* L) {
    //check_empty_list(L, "List_size");
    return L->size;
}

int List_get_first_val(const List* L) {
    check_empty_list(L, "List_first_val");
    return L->begin->val;
}

int List_get_last_val(const List* L) {
    check_empty_list(L, "List_last_val");
    return L->end->val;
}

int List_get_val(const List* L, int index) {
    check_empty_list(L, "List_get_val");

    if (index < 0 || index >= L->size) {
        fprintf(stderr, "ERROR in 'List_get_val'\n");
        fprintf(stderr, "invalid index: %d\n", index);
        fprintf(stderr, "Try an index within [0, %lu]\n", L->size - 1);
        exit(EXIT_FAILURE);
    }

    Node* p = L->begin;
    for (int i = 0; i != index; i++) {
        p = p->next;
    }

    return p->val;
}