#include "graph.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef struct _graph {
    int num_vertices;
    List** adjacency_list;
    float** weights;
} Graph;

Graph* graph_create(int num_vertices) {
    Graph* G = (Graph*)calloc(1, sizeof(Graph));
    if (G != NULL) {
        G->num_vertices = num_vertices;

        G->adjacency_list = (List**)calloc(num_vertices, sizeof(List*));
        G->weights = (float**)calloc(num_vertices, sizeof(float*));

        for (int i = 0; i < num_vertices; i++) {
            G->adjacency_list[i] = List_create();
            G->weights[i] = (float*)calloc(num_vertices, sizeof(float));
        }
    }
    return G;
}

void destroy_graph(Graph* G) {
    if (G != NULL) {
        for (int i = 0; i < G->num_vertices; i++) {
            List_destroy(&(G->adjacency_list[i]));
        }
        free(G->adjacency_list);

        free(G);
    }
}

int get_num_vertices(Graph* G) {
    if (G != NULL) {
        return G->num_vertices;
    }
    return 0;
}

int insert_edge(Graph* G, int origin, int destination, int is_directed, float weight) {
    if (G == NULL) {
        return 0;
    }

    if (origin < 0 || origin >= G->num_vertices || destination < 0 || destination >= G->num_vertices) {
        return 0;
    }

    List_add_last(G->adjacency_list[origin], destination);
    G->weights[origin][destination] = weight;

    if (!is_directed) {
        List_add_last(G->adjacency_list[destination], origin);
        G->weights[destination][origin] = weight;
    }

    return 1;
}

int remove_edge(Graph* G, int origin, int destination, int is_directed) {
    if (G == NULL) {
        return 0;
    }

    if (origin < 0 || origin >= G->num_vertices || destination < 0 || destination >= G->num_vertices) {
        return 0;
    }

    size_t position = find_node_position(G->adjacency_list[origin], destination);

    if (position < List_size(G->adjacency_list[origin])) {
        remove_at(G->adjacency_list[origin], position);
        G->weights[origin][destination] = 0.0;
    }
    else {
        return 0;
    }

    if (!is_directed) {
        remove_edge(G, destination, origin, 1);
    }

    return 1;
}


void print_graph(Graph* G) {
    if (G == NULL) {
        return;
    }

    for (int i = 0; i < G->num_vertices; i++) {
        printf("%d: ", i);

        List* adjacency_list = G->adjacency_list[i];
        size_t list_size = List_size(adjacency_list);

        for (size_t j = 0; j < list_size; j++) {
            int neighbor = List_get_val(adjacency_list, j);
            float weight = G->weights[i][neighbor];
            printf("%d(%.1f), ", neighbor, weight);
        }

        puts("");
    }
}

int find_minimum_distance(float* distance, int* visited, int num_vertices) {
    int smallest = -1, first = 1;
    for (int i = 0; i < num_vertices; i++) {
        if (distance[i] >= 0 && visited[i] == 0) {
            if (first || distance[smallest] > distance[i]) {
                smallest = i;
                first = 0;
            }
        }
    }
    return smallest;
}

void shortest_path_graph(Graph* G, int start, int* predecessor, float* distance) {
    int count, num_vertices, * visited, vertex;

    count = num_vertices = G->num_vertices;
    visited = (int*)malloc(num_vertices * sizeof(int));

    for (int i = 0; i < num_vertices; i++) {
        predecessor[i] = -1;
        distance[i] = -1;
        visited[i] = 0;
    }

    distance[start] = 0;

    while (count > 0) {
        vertex = find_minimum_distance(distance, visited, num_vertices);

        if (vertex == -1) {
            break;
        }

        visited[vertex] = 1;
        count--;

        // Acesso aos vizinhos usando listas de adjacência
        List* neighbors = G->adjacency_list[vertex];
        size_t num_neighbors = List_size(neighbors);

        for (size_t i = 0; i < num_neighbors; i++) {
            int index = List_get_val(neighbors, i);
            float weight = G->weights[vertex][index];

            if (distance[index] < 0 || distance[index] > distance[vertex] + weight) {
                distance[index] = distance[vertex] + weight;
                predecessor[index] = vertex;
            }
        }
    }

    free(visited);
}

void print_pre_and_post_order(int num_vertices, int* pre_order, int* post_order) {
    printf("Pre-order traversal: ");
    for (int i = 0; i < num_vertices; i++) {
        printf("%d ", pre_order[i]);
    }
    printf("\n");

    printf("Post-order traversal: ");
    for (int i = 0; i < num_vertices; i++) {
        printf("%d ", post_order[i]);
    }
    printf("\n");
}

void depth_first_search_recursive(Graph* G, int start, int* visited, int count, int* pre_order, int* post_order) {
    visited[start] = count;

    pre_order[start] = count;

    List* neighbors = G->adjacency_list[start];
    size_t num_neighbors = List_size(neighbors);

    for (size_t i = 0; i < num_neighbors; i++) {
        int neighbor = List_get_val(neighbors, i);
        if (!visited[neighbor]) {
            depth_first_search_recursive(G, neighbor, visited, count + 1, pre_order, post_order);
        }
    }

    post_order[start] = ++count;
}

void depth_first_search(Graph* G, int start, int* visited, int* pre_order, int* post_order) {
    int count = 1;

    for (int i = 0; i < G->num_vertices; i++) {
        visited[i] = 0;
        pre_order[i] = 0;
        post_order[i] = 0;
    }

    depth_first_search_recursive(G, start, visited, count, pre_order, post_order);

    print_pre_and_post_order(G->num_vertices, pre_order, post_order);
}

void breadth_first_search(Graph* G, int start, int* visited, int* pre_order, int* post_order) {
    int num_vertices = G->num_vertices;
    int count = 1;

    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
        pre_order[i] = 0;
        post_order[i] = 0;
    }

    int* queue = (int*)malloc(num_vertices * sizeof(int));
    int front = 0, rear = 0;

    rear++;
    queue[rear] = start;
    visited[start] = count;

    while (front != rear) {
        front = (front + 1) % num_vertices;
        int current_vertex = queue[front];
        count++;

        pre_order[current_vertex] = count;

        List* neighbors = G->adjacency_list[current_vertex];
        size_t num_neighbors = List_size(neighbors);

        for (size_t i = 0; i < num_neighbors; i++) {
            int neighbor = List_get_val(neighbors, i);
            if (!visited[neighbor]) {
                rear = (rear + 1) % num_vertices;
                queue[rear] = neighbor;
                visited[neighbor] = count;
            }
        }

        post_order[current_vertex] = count;
    }

    free(queue);

    print_pre_and_post_order(num_vertices, pre_order, post_order);
}