#include "list.h"
#include <stdio.h>


int main() {
    List* L = List_create();

    List_print(L);
    List_inverted_print(L);

    puts("Remove 99");
    List_remove(L, 99);
    List_print(L);
    List_inverted_print(L);

    puts("add_last 10, 7, 2, 4, 7");
    List_add_last(L, 10);
    List_add_last(L, 7);
    List_add_last(L, 2);
    List_add_last(L, 4);
    List_add_last(L, 7);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 99");
    List_remove(L, 99);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 7");
    List_remove(L, 7);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 10");
    List_remove(L, 10);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 4");
    List_remove(L, 4);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 7");
    List_remove(L, 7);
    List_print(L);
    List_inverted_print(L);

    puts("Remove 2");
    List_remove(L, 2);
    List_print(L);
    List_inverted_print(L);

    printf("--------------------------------");

    puts("\nadd_last 10, 7, 2, 4, 7");
    List_add_last(L, 10);
    List_add_last(L, 7);
    List_add_last(L, 2);
    List_add_last(L, 4);
    List_add_last(L, 7);
    List_print(L);

    printf("\nFirst: %d\n", List_first_val(L));
    printf("Last: %d\n", List_last_val(L));
    printf("Get[0]: %d\n", List_get_val(L, 0));
    printf("Get[1]: %d\n", List_get_val(L, 1));
    printf("Get[2]: %d\n", List_get_val(L, 2));
    printf("Get[3]: %d\n", List_get_val(L, 3));

    List_destroy(&L);

    return 0;
}