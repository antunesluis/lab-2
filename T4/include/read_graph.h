#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include "graph.h"
#include "list.h"

void read_graph(Graph* G);

void read_short_path(Graph* G);
void read_breadth_or_depth_search(Graph* G, int option);
void read_edge_to_add(Graph* G);
void read_edge_to_remove(Graph* G);

#include <stdbool.h>
#include <stddef.h>

#endif