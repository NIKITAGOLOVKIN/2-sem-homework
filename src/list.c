#include "airports.h"
#include <stdio.h>
#include <string.h>

ListNode* createList(char* filename)
{
    FILE* file = fopen(filename, "r");
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
    ListNode* newNode = calloc(1, sizeof(ListNode));
    newNode->code = malloc(strlen(code) + 1);
    strcpy(newNode->code, code);
    newNode->name = malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    newNode->next = list;
    return newNode;
}

void listFind(ListNode* node, char* str)
{
    while (node) {
        if (strcmp(str, node->code) == 0) {
            printf("%s -> %s.\n", node->code, node->name);
            return;
        }
        node = node->next;
    }
    printf("Аэропорт с кодом '%s' не найден в базе.\n", str);
}

int listFindSilent(ListNode* node, char* str)
{
    while (node) {
        if (strcmp(str, node->code) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

ListNode* listDelete(ListNode* list, char* code)
{
    if (list == NULL) {
        return NULL;
    }

    ListNode* temp = list;
    if (strcmp(list->code, code) == 0) {
        list = list->next;
        free(temp->code);
        free(temp->name);
        free(temp);
        return list;
    }

    ListNode* prev = NULL;
    while (temp) {
        if (strcmp(code, temp->code) == 0) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
        return list;
    }

    prev->next = temp->next;
    free(temp->code);
    free(temp->name);
    free(temp);
    return list;
}

void freeList(ListNode* list)
{
    while (list) {
        ListNode* temp = list;
        list = list->next;
        free(temp->code);
        free(temp->name);
        free(temp);
    }
}