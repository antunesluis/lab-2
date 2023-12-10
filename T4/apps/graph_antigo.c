#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef struct _graph {
    int is_weighted;
    int num_vertices;
    int max_degree;
    int** edges;
    float** weights;
    int* degree;
} Graph;

Graph* graph_create(int num_vertices, int max_degree, int is_weighted) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    if (G != NULL) {
        G->num_vertices = num_vertices;
        G->max_degree = max_degree;
        G->is_weighted = (is_weighted != 0) ? true : false;
        G->degree = (int*)calloc(num_vertices, sizeof(int));

        G->edges = (int**)malloc(num_vertices * sizeof(int*));

        for (int i = 0; i < num_vertices; i++) {
            G->edges[i] = (int*)malloc(max_degree * sizeof(int));
        }

        if (G->is_weighted) {
            G->weights = (float**)malloc(num_vertices * sizeof(float*));

            for (int i = 0; i < num_vertices; i++) {
                G->weights[i] = (float*)malloc(max_degree * sizeof(float));
            }
        }
    }
    return G;
}

void destroy_graph(Graph* G) {
    if (G != NULL) {
        for (int i = 0; i < G->num_vertices; i++) {
            free(G->edges[i]);
        }
        free(G->edges);

        if (G->is_weighted) {
            for (int i = 0; i < G->num_vertices; i++) {
                free(G->weights[i]);
            }
            free(G->weights);
        }

        free(G->degree);
        free(G);
    }
}

void get_num_vertices(Graph* G) {
    if (G != NULL) {
        return G->num_vertices;
    }
}

void get_max_degree(Graph* G) {
    if (G != NULL) {
        return G->max_degree;
    }
}

int insert_edge(Graph* G, int origin, int destination, int is_directed, float weight) {
    if (G == NULL) {
        return 0;
    }

    if (origin < 0 || origin >= G->num_vertices) {
        return 0;
    }

    if (destination < 0 || destination >= G->num_vertices) {
        return 0;
    }

    G->edges[origin][G->degree[origin]] = destination;

    if (G->is_weighted) {
        G->weights[origin][G->degree[origin]] = weight;
    }

    G->degree[origin]++;

    if (!is_directed) {
        insert_edge(G, destination, origin, 1, weight);
    }

    return 1;
}

int remove_edge(Graph* G, int origin, int destination, int is_directed) {
    if (G == NULL) {
        return 0;
    }

    if (origin < 0 || origin >= G->num_vertices) {
        return 0;
    }

    if (destination < 0 || destination >= G->num_vertices) {
        return 0;
    }

    int i = 0;
    while (i < G->degree[origin] && G->edges[origin][i] != destination) {
        i++;
    }

    if (i == G->degree[origin]) { // element not found
        return 0;
    }

    G->degree[origin]--;
    G->edges[origin][i] = G->edges[origin][G->degree[origin]];

    if (G->is_weighted) {
        G->weights[origin][i] = G->weights[origin][G->degree[origin]];
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
        for (int j = 0; j < G->degree[i]; j++) {
            if (G->is_weighted) {
                printf("%d(%.2f), ", G->edges[i][j], G->weights[i][j]);
            }
            else {
                printf("%d, ", G->edges[i][j]);
            }
        }
        puts("");
    }
}

int find_minimum_distance(float* distance, int* visited, int num_vertices) {
    int smallest = -1, first = 1;
    for (int i = 0; i < num_vertices; i++) {
        if (distance[i] >= 0 && visited[i] == 0) {
            if (first) {
                smallest = i;
                first = 0;
            }
            else {
                if (distance[smallest] > distance[i]) {
                    smallest = i;
                }
            }
        }
    }
    return smallest;
}

void shortest_path_graph(Graph* G, int start, int* predecessor, float* distance) {
    int count, num_vertices, index, * visited, vertex;

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

        for (int i = 0; i < G->degree[vertex]; i++) {
            index = G->edges[vertex][i];
            if (distance[index] < 0) {
                distance[index] = distance[vertex] + 1;
                predecessor[index] = vertex;
            }
            else {
                if (distance[index] > distance[vertex] + 1) {
                    distance[index] = distance[vertex] + 1;
                    predecessor[index] = vertex;
                }
            }
        }
    }

    free(visited);
}

void depth_first_search_recursive(Graph* G, int start, int* visited, int count) {
    int i;
    visited[start] = count;
    for (i = 0; i < G->degree[start]; i++) {
        if (!visited[G->edges[start][i]]) {
            depth_first_search_recursive(G, G->edges[start][i], visited, count + 1);
        }
    }
}

void depth_first_search(Graph* G, int start, int* visited) {
    int count = 1;
    for (int i = 0; i < G->num_vertices; i++) {
        visited[i] = 0;
    }

    depth_first_search_recursive(G, start, visited, count);

    for (int i = 0; i < G->num_vertices; i++) {
        printf("%d -> %d\n", i, visited[i]);
    }
}

void breadth_first_search(Graph* G, int start, int* visited) {
    int vertex, num_vertices, count = 1;
    int* queue, front = 0, rear = 0;

    for (int i = 0; i < G->num_vertices; i++) {
        visited[i] = 0;
    }

    num_vertices = G->num_vertices;
    queue = (int*)malloc(num_vertices * sizeof(int));
    rear++;
    queue[rear] = start;
    visited[start] = count;

    while (front != rear) {
        front = (front + 1) % num_vertices;
        vertex = queue[front];
        count++;

        for (int i = 0; i < G->degree[vertex]; i++) {
            if (!visited[G->edges[vertex][i]]) {
                rear = (rear + 1) % num_vertices;
                queue[rear] = G->edges[vertex][i];
                visited[G->edges[vertex][i]] = count;
            }
        }
    }

    free(queue);

    for (int i = 0; i < G->num_vertices; i++) {
        printf("%d -> %d\n", i, visited[i]);
    }
}

