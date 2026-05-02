#pragma once

typedef struct ListNode ListNode;

// Создание списка
ListNode* createList(char* filename);

// Вставка в список
ListNode* listInsert(ListNode* list, char* code, char* name);

// Поиск в списке
void listFind(ListNode* node, char* str);

// Удаление элемента списка
ListNode* listDelete(ListNode* list, char* code);

// Освобождение списка
void freeList(ListNode* list);