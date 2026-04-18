#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int len;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge** graph;
} Graph;

typedef struct HeapNode {
    int city;
    int dist;
} HeapNode;

typedef struct MinHeap {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

Graph* initGraph(int n);

void freeGraph(Graph* graph, int n);

Edge* createEdge(int to, int len);

Edge* pushEdge(Edge* list, Edge* edge);

void getEdge(FILE* file, Graph* graph, int m);

MinHeap* initMinHeap(void);

void swap(HeapNode* node1, HeapNode* node2);

void siftUp(MinHeap* heap, int i);

void siftDown(MinHeap* heap, int i);

void heapPush(MinHeap* heap, int city, int dist);

void heapPop(MinHeap* heap, HeapNode* root);

void freeHeap(MinHeap* heap);