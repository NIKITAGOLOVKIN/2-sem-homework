#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListNode* createListNode(char* code, char* name)
{
    ListNode* newNode = calloc(1, sizeof(ListNode));
    newNode->code = strdup(code);
    newNode->name = strdup(name);
    newNode->next = NULL;
    return newNode;
}

static void deleteListNode(ListNode* node)
{
    if (node) {
        free(node->code);
        free(node->name);
        free(node);
    }
}

ListNode* createList(char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("ошибка чтения файла\n");
        return NULL;
    }

    ListNode* list = NULL;
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
        list = listInsert(list, buffer, name + 1);
    }

    fclose(file);
    return list;
}

ListNode* listInsert(ListNode* list, char* code, char* name)
{
    ListNode* newNode = createListNode(code, name);
    newNode->next = list;
    return newNode;
}

ListNode* listFind(ListNode* node, char* str)
{
    while (node) {
        if (strcmp(str, node->code) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

ListNode* listDelete(ListNode* list, char* code)
{
    if (list == NULL) {
        return NULL;
    }

    if (strcmp(list->code, code) == 0) {
        ListNode* temp = list->next;
        deleteListNode(list);
        return temp;
    }

    ListNode* prev = list;
    ListNode* curr = list->next;

    while (curr) {
        if (strcmp(code, curr->code) == 0) {
            prev->next = curr->next;
            deleteListNode(curr);
            return list;
        }
        prev = curr;
        curr = curr->next;
    }

    return list;
}

void freeList(ListNode* list)
{
    while (list) {
        ListNode* temp = list;
        list = list->next;
        deleteListNode(temp);
    }
}