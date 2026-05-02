#include "states.h"
#include <stdlib.h>

typedef struct Edge {
    int to;
    int len;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge** graph;
} Graph;

Graph* initGraph(int n)
{
    Graph* newGraph = malloc(sizeof(Graph));
    Edge** graphList = malloc(n * sizeof(Edge*));
    if (newGraph == NULL) {
        free(graphList);
        return NULL;
    }
    if (graphList == NULL) {
        free(newGraph);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        graphList[i] = NULL;
    }
    newGraph->graph = graphList;

    return newGraph;
}

Edge* createEdge(int to, int len)
{
    Edge* newEdge = malloc(sizeof(Edge));
    if (newEdge == NULL) {
        return NULL;
    }

    newEdge->to = to;
    newEdge->len = len;
    newEdge->next = NULL;

    return newEdge;
}

Edge* pushEdge(Edge* list, Edge* edge)
{
    edge->next = list;
    list = edge;
    return list;
}

bool readEdge(FILE* file, Graph* graph, int m)
{
    for (int u = 0; u < m; ++u) {
        int i, j, len;
        fscanf(file, "%d %d %d", &i, &j, &len);
        i--;
        j--;

        Edge* edge1 = createEdge(j, len);
        Edge* edge2 = createEdge(i, len);

        if (edge1 == NULL) {
            free(edge2);
            return false;
        }
        if (edge2 == NULL) {
            free(edge1);
            return false;
        }
        graph->graph[i] = pushEdge(graph->graph[i], edge1);
        graph->graph[j] = pushEdge(graph->graph[j], edge2);
    }
    return true;
}

void freeGraph(Graph* graph, int n)
{
    for (int i = 0; i < n; i++) {
        Edge* curr = graph->graph[i];
        while (curr != NULL) {
            Edge* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->graph);
    free(graph);
}