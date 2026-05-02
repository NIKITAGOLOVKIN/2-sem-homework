#pragma once
#include <stdbool.h>

// структура элемента кучи
typedef struct {
    int city;
    int dist;
} HeapNode;

// структура кучи
typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

// Инициализация кучи
MinHeap* initMinHeap(void);

// Добавление нового элемента в кучу
bool heapPush(MinHeap* heap, int city, int dist);

// Взятие минимального элемента кучи
void heapPop(MinHeap* heap, HeapNode* root);

// Освобождение кучи
void freeHeap(MinHeap* heap);