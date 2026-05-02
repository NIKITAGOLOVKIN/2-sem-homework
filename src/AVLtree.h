#pragma once

typedef struct Node Node;

//
Node* createAVLtree(char* filename);

//
Node* insert(Node* node, char* code, char* name);

//
void freeTree(Node* node);

//
void find(Node* node, char* str);

//
Node* add(Node* node, char* str);

//
Node* deleteNode(Node* node, char* str);

//
void save(Node* node, char* filename);