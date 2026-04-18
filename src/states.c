#include "states.h"

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

void getEdge(FILE* file, Graph* graph, int m)
{
    for (int u = 0; u < m; ++u) {
        int i, j, len;
        fscanf(file, "%d %d %d", &i, &j, &len);
        i--;
        j--;

        Edge* edge1 = createEdge(j, len);
        Edge* edge2 = createEdge(i, len);
        graph->graph[i] = pushEdge(graph->graph[i], edge1);
        graph->graph[j] = pushEdge(graph->graph[j], edge2);
    }
}

MinHeap* initMinHeap(void)
{
    MinHeap* heap = malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->size = 0;
    heap->capacity = 10;

    HeapNode* heapElements = malloc(sizeof(HeapNode) * heap->capacity);
    if (heapElements == NULL) {
        free(heap);
        return NULL;
    }

    heap->data = heapElements;

    return heap;
}

void swap(HeapNode* node1, HeapNode* node2)
{
    HeapNode temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void siftUp(MinHeap* heap, int i)
{
    while ((i > 0) && (heap->data[i].dist < heap->data[(i - 1) / 2].dist)) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void siftDown(MinHeap* heap, int i)
{
    while (2 * i + 1 < heap->size) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int smallest = leftChild;
        
        if (rightChild < heap->size) {
            if (heap->data[rightChild].dist < heap->data[leftChild].dist) {
                smallest = rightChild;
            } else if (heap->data[rightChild].dist == heap->data[leftChild].dist) {
                if (heap->data[rightChild].city < heap->data[leftChild].city) {
                    smallest = rightChild;
                }
            }
        }

        if (heap->data[i].dist < heap->data[smallest].dist) {
            break;
        }
        if (heap->data[i].dist == heap->data[smallest].dist && heap->data[i].city <= heap->data[smallest].city) {
            break;
        }

        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        i = smallest;
    }
}

void heapPush(MinHeap* heap, int city, int dist)
{
    if (heap->size >= heap->capacity) {
        int newCapacity = heap->capacity * 2;
        HeapNode* newNodes = realloc(heap->data, newCapacity * sizeof(HeapNode));
        heap->capacity = newCapacity;
        heap->data = newNodes;
    }

    heap->data[heap->size].city = city;
    heap->data[heap->size].dist = dist;

    siftUp(heap, heap->size);
    heap->size++;
}

void heapPop(MinHeap* heap, HeapNode* root)
{

    *root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    siftDown(heap, 0);
}

void freeHeap(MinHeap* heap)
{
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}