#include "read_graph.h"
#include "graph.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef enum {
    ADD_EDGES,
    DELETE_EDGES,
    PRINT_GRAPH,
    TRAVERSE_BFS,
    TRAVERSE_DFS,
    SHORT_PATH,
    EXIT
} MenuOption;

void clear_terminal() {
    printf("\033[H\033[J"); // Sequência de escape ANSI para limpar o terminal
}

void press_enter_continue() {
    puts("");
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n');
}

void consume_newline() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool validate_vertex_index(int vertex, int num_vertices) {
    if (vertex < 0 || vertex >= num_vertices) {
        printf("Índice inválido. Por favor, digite um valor entre 0 e %d.\n", num_vertices - 1);
        return false;
    }
    return true;
}

int read_integer(const char* prompt) {
    int value;

    printf("\n%s", prompt);

    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');

        printf("Por favor, digite um número inteiro válido: ");
    }
    puts("");

    return value;
}

int get_menu_options() {
    puts("");
    printf("Digite a ação desejada:\n");
    printf("\t0. Adicionar Vértice\n");
    printf("\t1. Deletar Vértice\n");
    printf("\t2. Mostrar Grafo\n");
    printf("\t3. Busca em largura\n");
    printf("\t4. Busca em profundidade\n");
    printf("\t5. Menor Caminho\n");
    printf("\t6. Sair\n");
    puts("");

    int option = read_integer("\nDigite a opção desejada: ");
    return option;
}

int read_vertex_index(const char* prompt, int num_vertices) {
    int vertex;
    do {
        vertex = read_integer(prompt);
    } while (!validate_vertex_index(vertex, num_vertices));

    return vertex;
}

int read_start_vertex(int num_vertices) {
    return read_vertex_index("\nDigite o vértice de início: ", num_vertices);
}

int read_destination_vertex(int num_vertices) {
    return read_vertex_index("Digite o vértice de destino: ", num_vertices);
}

void read_edge_to_add(Graph* G) {
    printf("---- Adicionando Aresta ----");

    int num_vertices = get_num_vertices(G);

    int start_vertex = read_start_vertex(num_vertices);
    int destination_vertex = read_destination_vertex(num_vertices);

    if (!validate_vertex_index(start_vertex, num_vertices) ||
        !validate_vertex_index(destination_vertex, num_vertices)) {
        return;
    }

    int weight = read_integer("Digite o peso da aresta: ");

    insert_edge(G, start_vertex, destination_vertex, 0, weight);
}

void read_edge_to_remove(Graph* G) {
    printf("---- Removendo Aresta ----");

    int num_vertices = get_num_vertices(G);

    int start_vertex = read_start_vertex(num_vertices);
    int destination_vertex = read_destination_vertex(num_vertices);

    if (!validate_vertex_index(start_vertex, num_vertices) ||
        !validate_vertex_index(destination_vertex, num_vertices)) {
        return;
    }

    remove_edge(G, start_vertex, destination_vertex, 0);
}

void read_breadth_or_depth_search(Graph* G, int option) {
    printf("\n--- Lendo Vertices ----");

    int num_vertices = get_num_vertices(G);
    int start_vertex = read_start_vertex(num_vertices);

    int* visited = (int*)calloc(num_vertices, sizeof(int));
    int* pre_order = (int*)calloc(num_vertices, sizeof(int));
    int* post_order = (int*)calloc(num_vertices, sizeof(int));

    if (option == TRAVERSE_BFS) {
        printf("---- Busca em Largura ----\n");
        breadth_first_search(G, start_vertex, visited, pre_order, post_order);
    }

    if (option == TRAVERSE_DFS) {
        printf("---- Busca em Profundidade ----\n");
        depth_first_search(G, start_vertex, visited, pre_order, post_order);
    }

    free(visited);
    free(pre_order);
    free(post_order);
}

void print_shortest_path_result(int num_vertices, int* predecessor, float* distance) {
    printf("Vértice\tPredecessor\tDistância\n");

    for (int i = 0; i < num_vertices; i++) {
        printf("%d\t%d\t\t%.2f\n", i, predecessor[i], distance[i]);
    }
}

void read_short_path(Graph* G) {
    int num_vertices = get_num_vertices(G);
    int start_vertex = read_start_vertex(num_vertices);

    int* predecessor = (int*)calloc(num_vertices, sizeof(int));
    float* distance = (float*)calloc(num_vertices, sizeof(float));

    shortest_path_graph(G, start_vertex, predecessor, distance);

    print_shortest_path_result(num_vertices, predecessor, distance);

    free(predecessor);
    free(distance);
}

void read_graph(Graph* G) {
    int option;

    do {
        clear_terminal();
        option = get_menu_options();

        switch (option) {
        case ADD_EDGES:
            read_edge_to_add(G);
            break;
        case DELETE_EDGES:
            read_edge_to_remove(G);
            break;
        case PRINT_GRAPH:
            print_graph(G);
            break;
        case TRAVERSE_BFS:
            read_breadth_or_depth_search(G, option);
            break;
        case TRAVERSE_DFS:
            read_breadth_or_depth_search(G, option);
            break;
        case SHORT_PATH:
            read_short_path(G);
            break;
        case EXIT:
            break;
        default:
            printf("Opção inválida\n");
            break;
        }

        consume_newline();
        press_enter_continue();
    } while (option != EXIT);
}
