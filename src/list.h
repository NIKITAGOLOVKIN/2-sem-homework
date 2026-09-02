#pragma once

typedef struct ListNode {
    char* code;
    char* name;
    struct ListNode* next;
} ListNode;

// Создание списка
ListNode* createList(char* fileName);

// Вставка в список
ListNode* listInsert(ListNode* list, char* code, char* name);

// Поиск в списке
ListNode* listFind(ListNode* node, char* str);

// Удаление элемента списка
ListNode* listDelete(ListNode* list, char* code);

// Освобождение списка
void freeList(ListNode* list);