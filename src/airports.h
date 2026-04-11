#pragma once

#include <stdlib.h>

typedef struct Node {
    struct Node* leftChild;
    struct Node* rightChild;
    int balance;
    char* code;
    char* name;
} Node;

typedef struct ListNode {
    char* code;
    char* name;
    struct ListNode* next;
} ListNode;

Node* createAVLtree(char* filename);

ListNode* createList(char* filename);

int workWithList(char* filename);

int workWithAVLTree(char* filename);

Node* insert(Node* node, char* code, char* name);

int getHeight(Node* node);

void inorderPrint(Node* node);

Node* balance(Node* node);

Node* rotateLeft(Node* node);

Node* rotateRight(Node* node);

Node* bigRotateLeft(Node* node);

Node* bigRotateRight(Node* node);

void freeTree(Node* node);

void find(Node* node, char* str);

int findSilent(Node* node, char* str);

Node* add(Node* node, char* str);

Node* deleteNode(Node* node, char* str);

void save(Node* node, char* filename);

ListNode* listInsert(ListNode* list, char* code, char* name);

void listFind(ListNode* node, char* str);

int listFindSilent(ListNode* node, char* str);

ListNode* listDelete(ListNode* list, char* code);

void freeList(ListNode* list);

void firstScenarioAVL(Node* root, char** requests, int count);

void firstScenarioList(ListNode* list, char** requests, int count);

void secondScenarioAVL(Node** root, char** requests, char** newCodes, int count);

void secondScenarioList(ListNode** list, char** requests, char** newCodes, int count);