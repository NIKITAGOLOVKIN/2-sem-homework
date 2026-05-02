#pragma once

typedef struct ListNode ListNode;

//
ListNode* createList(char* filename);

//
ListNode* listInsert(ListNode* list, char* code, char* name);

//
void listFind(ListNode* node, char* str);

//
ListNode* listDelete(ListNode* list, char* code);

//
void freeList(ListNode* list);