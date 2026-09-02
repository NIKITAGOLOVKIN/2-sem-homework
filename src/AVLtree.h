#pragma once

typedef struct Node {
    struct Node* leftChild;
    struct Node* rightChild;
    int height;
    char* code;
    char* name;
} Node;

// Создание узла дерева
Node* createNode(char* code, char* name);

// Освобождение узла дерева
void destroyNode(Node* node);

// Создание АВЛ дерева
Node* createAVLtree(char* fileName);

// Вставка в АВЛ дерево при чтении из файла
Node* insert(Node* node, char* code, char* name);

// Освобождение АВЛ дерева
void freeTree(Node* node);

// Поиск в АВЛ дереве
Node* find(Node* node, char* str);

// Добавление в АВЛ дерево элемента в интерактивном формате
Node* add(Node* node, char* str);

// Удаление элемента АВЛ дерева
Node* deleteNode(Node* node, char* str);

// Сохранение базы аэропортов в текстовый файл
void save(Node* root, char* fileName);