#include "read_graph.h"
#include <stdio.h>

int main() {
    int num_vertices;

    printf("\nDigite o numero de vertices do grafo: ");
    while (scanf("%d", &num_vertices) != 1) {
        while (getchar() != '\n');
        printf("\nPor favor, digite um número inteiro válido: ");
    }

    Graph* G = graph_create(num_vertices);

    if (G != NULL) {
        read_graph(G);
    }

    destroy_graph(G);

    return 0;
}
