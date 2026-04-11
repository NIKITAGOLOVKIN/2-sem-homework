#include "airports.h"
#include <stdio.h>
#include <string.h>

int getHeight(Node* node)
{
    if (node == NULL) {
        return 0;
    }
    int heightLeft = getHeight(node->leftChild);
    int heightRight = getHeight(node->rightChild);
    return 1 + (heightLeft > heightRight ? heightLeft : heightRight);
}

Node* createAVLtree(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ошибка чтения файла\n");
        return NULL;
    }

    Node* root = NULL;
    char buffer[1000];

    while (fgets(buffer, sizeof(buffer), file)) {
        char* temp = strchr(buffer, '\n');
        if (temp == NULL)
            continue;
        *temp = '\0';
        if (buffer[0] == '\0')
            continue;

        char* name = strchr(buffer, ':');
        if (name == NULL)
            continue;
        *name = '\0';
        root = insert(root, buffer, name + 1);
    }

    fclose(file);
    return root;
}

Node* rotateLeft(Node* node)
{
    Node* right = node->rightChild;
    Node* temp = right->leftChild;
    right->leftChild = node;
    node->rightChild = temp;

    node->balance = getHeight(node->rightChild) - getHeight(node->leftChild);
    right->balance = getHeight(right->rightChild) - getHeight(right->leftChild);
    return right;
}

Node* rotateRight(Node* node)
{
    Node* left = node->leftChild;
    Node* temp = left->rightChild;
    left->rightChild = node;
    node->leftChild = temp;

    node->balance = getHeight(node->rightChild) - getHeight(node->leftChild);
    left->balance = getHeight(left->rightChild) - getHeight(left->leftChild);
    return left;
}

Node* bigRotateLeft(Node* node)
{
    node->rightChild = rotateRight(node->rightChild);
    return rotateLeft(node);
}

Node* bigRotateRight(Node* node)
{
    node->leftChild = rotateLeft(node->leftChild);
    return rotateRight(node);
}

Node* balance(Node* node)
{
    if (node->balance == 2) {
        if (node->rightChild->balance >= 0)
            return rotateLeft(node);
        return bigRotateLeft(node);
    }
    if (node->balance == -2) {
        if (node->leftChild->balance <= 0)
            return rotateRight(node);
        return bigRotateRight(node);
    }
    return node;
}

void inorderPrint(Node* node)
{
    if (node == NULL)
        return;

    inorderPrint(node->leftChild);
    printf("%s\n", node->code);
    inorderPrint(node->rightChild);
}

Node* insert(Node* node, char* code, char* name)
{
    if (node == NULL) {
        Node* newNode = calloc(1, sizeof(Node));
        newNode->code = malloc(strlen(code) + 1);
        strcpy(newNode->code, code);
        newNode->name = malloc(strlen(name) + 1);
        strcpy(newNode->name, name);
        newNode->balance = 0;
        return newNode;
    }
    if (strcmp(code, node->code) < 0) {
        node->leftChild = insert(node->leftChild, code, name);
    } else {
        node->rightChild = insert(node->rightChild, code, name);
    }

    node->balance = getHeight(node->rightChild) - getHeight(node->leftChild);
    return balance(node);
}

void freeTree(Node* node)
{
    if (node == NULL)
        return;
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    free(node->code);
    free(node->name);
    free(node);
}

void find(Node* node, char* str)
{
    while (node) {
        int temp = strcmp(str, node->code);
        if (temp == 0) {
            printf("%s -> %s.\n", node->code, node->name);
            return;
        }
        if (temp < 0) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    printf("Аэропорт с кодом '%s' не найден в базе.\n", str);
}

int findSilent(Node* node, char* str)
{
    while (node) {
        int temp = strcmp(str, node->code);
        if (temp == 0) {
            return 1;
        }
        if (temp < 0) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    return 0;
}

Node* add(Node* node, char* str)
{
    char* name = strchr(str, ':');
    *name = '\0';
    node = insert(node, str, name + 1);
    return node;
}

Node* deleteNode(Node* node, char* str)
{
    if (node == NULL) {
        return NULL;
    }

    int temp = strcmp(str, node->code);
    if (temp < 0) {
        node->leftChild = delete (node->leftChild, str);
    } else if (temp > 0) {
        node->rightChild = delete (node->rightChild, str);
    } else {
        if (!node->leftChild && !node->rightChild) {
            free(node->name);
            free(node->code);
            free(node);
            return NULL;
        }
        if (node->leftChild == NULL) {
            Node* temp = node->rightChild;
            free(node->name);
            free(node->code);
            free(node);
            return temp;
        }
        if (node->rightChild == NULL) {
            Node* temp = node->leftChild;
            free(node->name);
            free(node->code);
            free(node);
            return temp;
        }

        Node* successor = node->rightChild;
        while (successor->leftChild) {
            successor = successor->leftChild;
        }

        free(node->code);
        node->code = malloc(strlen(successor->code) + 1);
        strcpy(node->code, successor->code);
        free(node->name);
        node->name = malloc(strlen(successor->name) + 1);
        strcpy(node->name, successor->name);

        node->rightChild = delete (node->rightChild, successor->code);
    }

    node->balance = getHeight(node->rightChild) - getHeight(node->leftChild);
    return balance(node);
}

void printIntoFile(FILE* file, Node* node)
{
    if (node == NULL) {
        return;
    }
    printIntoFile(file, node->leftChild);
    fprintf(file, "%s:%s\n", node->code, node->name);
    printIntoFile(file, node->rightChild);
}

void save(Node* root, char* filename)
{
    FILE* file = fopen(filename, "w");
    printIntoFile(file, root);
    fclose(file);
    printf("Состояние базы сохранено\n");
}