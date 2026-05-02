#pragma once

// структура элемента кучи
typedef struct HeapNode HeapNode;

// структура кучи
typedef struct MinHeap MinHeap;

// Инициализация кучи
MinHeap* initMinHeap(void);

// Меняем местами два элемента кучи
void swap(HeapNode* node1, HeapNode* node2);

// Просеивание вверх 
void siftUp(MinHeap* heap, int i);

// Просеивание вниз
void siftDown(MinHeap* heap, int i);

// Добавление нового элемента в кучу
void heapPush(MinHeap* heap, int city, int dist);

// Взятие минимального элемента кучи
void heapPop(MinHeap* heap, HeapNode* root);

// Освобождение кучи
void freeHeap(MinHeap* heap);