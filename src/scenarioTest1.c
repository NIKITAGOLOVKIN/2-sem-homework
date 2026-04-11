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

void firstScenarioAVL(Node* root, char** requests, int count)
{
    int temp = 0;
    for (int i = 0; i < count; i++) {
        if (findSilent(root, requests[i])) {
            temp++;
        }
    }
}

void firstScenarioList(ListNode* list, char** requests, int count)
{
    int temp = 0;
    for (int i = 0; i < count; i++) {
        if (listFindSilent(list, requests[i])) {
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

    char* filename = argv[2];
    char* allCodes[10000];
    int codesCount = 0;
    char* requests[50000];
    srand(time(NULL));

    if (strcmp(argv[1], "avl") == 0) {

        Node* root = createAVLtree(filename);
        collectCodes(root, allCodes, &codesCount);

        for (int i = 0; i < 50000; i++) {
            requests[i] = allCodes[rand() % codesCount];
        }

        firstScenarioAVL(root, requests, 50000);
        freeTree(root);

    } else if (strcmp(argv[1], "list") == 0) {

        ListNode* list = createList(filename);
        collectListCodes(list, allCodes, &codesCount);

        for (int i = 0; i < 50000; i++) {
            requests[i] = allCodes[rand() % codesCount];
        }

        firstScenarioList(list, requests, 50000);
        freeList(list);

    } else {
        printf("Использование: %s [avl|list] airports.txt\n", argv[0]);
        return 1;
    }

    return 0;
}