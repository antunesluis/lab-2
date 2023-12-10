#ifndef GRAPH_H
#define GRAPH_H

#include "graph.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

typedef struct _graph Graph;

Graph* graph_create(int num_vertices);
void destroy_graph(Graph* G);
int get_num_vertices(Graph* G);
int insert_edge(Graph* G, int origin, int destination, int is_directed, float weight);
int remove_edge(Graph* G, int origin, int destination, int is_directed);
void print_graph(Graph* G);
int find_minimum_distance(float* distance, int* visited, int num_vertices);
void shortest_path_graph(Graph* G, int start, int* predecessor, float* distance);
void depth_first_search(Graph* G, int start, int* visited, int* pre_order, int* post_order);
void breadth_first_search(Graph* G, int start, int* visited, int* pre_order, int* post_order);

#endif