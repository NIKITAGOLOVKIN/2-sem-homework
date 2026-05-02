#pragma once

#include <stdbool.h>
#include <stdio.h>

// Структура ребра графа
typedef struct Edge Edge;

// Структура графа
typedef struct Graph Graph;

// Инициализация графа
Graph* initGraph(int n);

// Освобождение графа
void freeGraph(Graph* graph, int n);

// Создание ребра графа
Edge* createEdge(int to, int len);

// Добавление ребра в граф
Edge* pushEdge(Edge* list, Edge* edge);

// Чтение всех ребер из файла
bool readEdge(FILE* file, Graph* graph, int m);