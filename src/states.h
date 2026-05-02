#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Edge Edge;

typedef struct Graph Graph;

Graph* initGraph(int n);

void freeGraph(Graph* graph, int n);

Edge* createEdge(int to, int len);

Edge* pushEdge(Edge* list, Edge* edge);

bool readEdge(FILE* file, Graph* graph, int m);