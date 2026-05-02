#pragma once

typedef struct Node Node;

// Создание АВЛ дерева
Node* createAVLtree(char* filename);

// Вставка в АВЛ дерево при чтении из файла
Node* insert(Node* node, char* code, char* name);

// Освобождение АВЛ дерева
void freeTree(Node* node);

// Поиск в АВЛ дереве
void find(Node* node, char* str);

// Добавление в АВЛ дерево элемента в интерактивном формате
Node* add(Node* node, char* str);

// Удаление элемента АВЛ дерева
Node* deleteNode(Node* node, char* str);

// Сохранение базы аэропортов в текстовый файл
void save(Node* node, char* filename);