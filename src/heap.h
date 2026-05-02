#pragma once

typedef struct HeapNode HeapNode;

typedef struct MinHeap MinHeap;

MinHeap* initMinHeap(void);

void swap(HeapNode* node1, HeapNode* node2);

void siftUp(MinHeap* heap, int i);

void siftDown(MinHeap* heap, int i);

void heapPush(MinHeap* heap, int city, int dist);

void heapPop(MinHeap* heap, HeapNode* root);

void freeHeap(MinHeap* heap);