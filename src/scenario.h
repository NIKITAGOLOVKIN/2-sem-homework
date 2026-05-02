#pragma once

typedef struct Node Node;
typedef struct ListNode ListNode;

void firstScenarioAVL(Node* root, char** requests, int count);

void firstScenarioList(ListNode* list, char** requests, int count);

void secondScenarioAVL(Node** root, char** requests, char** newCodes, int count);

void secondScenarioList(ListNode** list, char** requests, char** newCodes, int count);