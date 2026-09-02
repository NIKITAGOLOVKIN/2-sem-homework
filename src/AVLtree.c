#include "AVLtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getHeight(Node* node)
{
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void updateHeight(Node* node)
{
    if (node == NULL) {
        return;
    }

    node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));
}

int getBalance(Node* node)
{
    if (node == NULL) {
        return 0;
    }

    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

Node* createNode(char* code, char* name)
{
    Node* newNode = calloc(1, sizeof(Node));

    newNode->code = malloc(strlen(code) + 1);
    strcpy(newNode->code, code);

    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);

    newNode->height = 1;

    return newNode;
}

void destroyNode(Node* node)
{
    if (node) {
        free(node->code);
        free(node->name);
        free(node);
    }
}

Node* createAVLtree(char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
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

    updateHeight(node);
    updateHeight(right);

    return right;
}

Node* rotateRight(Node* node)
{
    Node* left = node->leftChild;
    Node* temp = left->rightChild;
    left->rightChild = node;
    node->leftChild = temp;

    updateHeight(node);
    updateHeight(left);

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
    int balanceOfNode = getBalance(node);

    if (balanceOfNode == 2) {
        if (getBalance(node->rightChild) >= 0) {
            return rotateLeft(node);
        }

        return bigRotateLeft(node);
    }

    if (balanceOfNode == -2) {
        if (getBalance(node->leftChild) <= 0) {
            return rotateRight(node);
        }

        return bigRotateRight(node);
    }

    return node;
}

Node* insert(Node* node, char* code, char* name)
{
    if (node == NULL) {
        return createNode(code, name);
    }

    if (strcmp(code, node->code) < 0) {
        node->leftChild = insert(node->leftChild, code, name);
    } else {
        node->rightChild = insert(node->rightChild, code, name);
    }

    updateHeight(node);

    return balance(node);
}

void freeTree(Node* node)
{
    if (node == NULL)
        return;
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    destroyNode(node);
}

Node* find(Node* node, char* str)
{
    while (node) {
        int temp = strcmp(str, node->code);
        if (temp == 0) {
            return node;
        }
        if (temp < 0) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    return NULL;
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
        node->leftChild = deleteNode(node->leftChild, str);
    } else if (temp > 0) {
        node->rightChild = deleteNode(node->rightChild, str);
    } else {

        if (node->leftChild == NULL) {
            Node* temp = node->rightChild;
            destroyNode(node);
            return temp;
        }

        if (node->rightChild == NULL) {
            Node* temp = node->leftChild;
            destroyNode(node);
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

        node->rightChild = deleteNode(node->rightChild, successor->code);
    }

    updateHeight(node);

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

void save(Node* root, char* fileName)
{
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
        return;
    printIntoFile(file, root);
    fclose(file);
}