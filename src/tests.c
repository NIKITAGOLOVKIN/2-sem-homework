#include "AVLtree.h"
#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void testAVLInsertAndFind()
{
    printf("--- Testing AVLInsertAndFind ---\n");

    Node* root = NULL;
    root = insert(root, "SVO", "Sheremetyevo");
    root = insert(root, "KUF", "Kurumoch International Airport");
    root = insert(root, "LED", "Pulkovo");

    Node* found = find(root, "SVO");
    assert(found != NULL);
    assert(strcmp(found->name, "Sheremetyevo") == 0);

    found = find(root, "XXX");
    assert(found == NULL);

    freeTree(root);
    printf("--- Testing AVLInsertAndFind passed! ---\n");
}

void testAVLDelete()
{
    printf("--- Testing AVLDelete ---\n");

    Node* root = NULL;
    root = insert(root, "A", "Airport A");
    root = insert(root, "B", "Airport B");
    root = insert(root, "C", "Airport C");

    root = deleteNode(root, "A");
    assert(find(root, "A") == NULL);
    assert(find(root, "B") != NULL);
    assert(find(root, "C") != NULL);

    root = deleteNode(root, "B");
    root = deleteNode(root, "C");
    assert(find(root, "B") == NULL);
    assert(find(root, "C") == NULL);

    freeTree(root);
    printf("--- Testing AVLDelete passed! ---\n");
}

void testListInsertAndFind()
{
    printf("--- Testing listInsertAndFind ---\n");

    ListNode* list = NULL;
    list = listInsert(list, "SVO", "Sheremetyevo");
    list = listInsert(list, "KUF", "Kurumoch International Airport");

    ListNode* found = listFind(list, "SVO");
    assert(found != NULL);
    assert(strcmp(found->name, "Sheremetyevo") == 0);

    found = listFind(list, "XXX");
    assert(found == NULL);

    freeList(list);
    printf("--- Testing listInsertAndFind passed! ---\n");
}

void testListDelete()
{
    printf("--- Testing listDelete ---\n");

    ListNode* list = NULL;
    list = listInsert(list, "A", "Airport A");
    list = listInsert(list, "B", "Airport B");

    list = listDelete(list, "A");
    assert(listFind(list, "A") == NULL);
    assert(listFind(list, "B") != NULL);

    list = listDelete(list, "B");
    assert(listFind(list, "B") == NULL);

    freeList(list);
    printf("--- Testing listDelete passed! ---\n");
}

void runTests(void)
{
    printf("--- Starting Tests! ---\n");

    testAVLInsertAndFind();
    testAVLDelete();
    testListInsertAndFind();
    testListDelete();

    printf("--- ALL Tests passed! ---\n");
}