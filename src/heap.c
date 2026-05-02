#include "heap.h"
#include <stdlib.h>

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

bool heapPush(MinHeap* heap, int city, int dist)
{
    if (heap->size >= heap->capacity) {
        int newCapacity = heap->capacity * 2;
        HeapNode* newNodes = realloc(heap->data, newCapacity * sizeof(HeapNode));
        if (!newNodes) {
            return false;
        }
        heap->capacity = newCapacity;
        heap->data = newNodes;
    }

    heap->data[heap->size].city = city;
    heap->data[heap->size].dist = dist;

    siftUp(heap, heap->size);
    heap->size++;

    return true;
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