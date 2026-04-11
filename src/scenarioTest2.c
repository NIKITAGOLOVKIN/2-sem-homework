#include "airports.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void collectCodes(Node* node, char** allCodes, int* count)
{
    if (node == NULL) {
        return;
    }
    collectCodes(node->leftChild, allCodes, count);
    allCodes[*count] = node->code;
    (*count)++;
    collectCodes(node->rightChild, allCodes, count);
}

void collectListCodes(ListNode* node, char** allCodes, int* count)
{
    while (node && *count < 10000) {
        allCodes[*count] = node->code;
        (*count)++;
        node = node->next;
    }
}

void secondScenarioAVL(Node** root, char** requests, char** newCodes, int count)
{
    int temp = 0;
    for (int i = 0; i < count; i++) {
        *root = insert(*root, newCodes[i], "New Airport");
        if (findSilent(*root, requests[i])) {
            temp++;
        }
    }
}

void secondScenarioList(ListNode** list, char** requests, char** newCodes, int count)
{
    int temp = 0;
    for (int i = 0; i < count; i++) {
        *list = listInsert(*list, newCodes[i], "New Airport");
        if (listFindSilent(*list, requests[i])) {
            temp++;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printf("Использование: %s [avl|list] airports.txt\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    char* filename = argv[2];
    char* allCodes[10000];
    char* requests[10000];
    char* newCodes[10000];
    int codesCount = 0;

    for (int i = 0; i < 10000; i++) {
        newCodes[i] = malloc(16);
        snprintf(newCodes[i], 16, "COD_%04d", i);
    }

    if (strcmp(argv[1], "avl") == 0) {

        Node* root = createAVLtree(filename);

        collectCodes(root, allCodes, &codesCount);

        for (int i = 0; i < 10000; i++) {
            requests[i] = allCodes[rand() % codesCount];
        }

        secondScenarioAVL(&root, requests, newCodes, 10000);
        freeTree(root);

        } else if (strcmp(argv[1], "list") == 0) {

        ListNode* list = createList(filename);

        collectListCodes(list, allCodes, &codesCount);

        for (int i = 0; i < 10000; i++) {
            requests[i] = allCodes[rand() % codesCount];
        }

        secondScenarioList(&list, requests, newCodes, 10000);
        freeList(list);

    } else {
        printf("Использование: %s [avl|list] airports.txt\n", argv[0]);
        for (int i = 0; i < 10000; i++) {
            free(newCodes[i]);
        }
        return 1;
    }

    for (int i = 0; i < 10000; i++) {
        free(newCodes[i]);
    }

    return 0;
}