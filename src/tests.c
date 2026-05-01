#include "dfa.h"

#include <assert.h>
#include <stdio.h>

void positiveTest(void)
{
    printf("--- Start positive tests ---\n");
    int n = 16;
    Transition table[16];

    table[0] = (Transition) { 0, 's', 1 };
    table[1] = (Transition) { 0, 'd', 2 };
    table[2] = (Transition) { 0, '.', 3 };
    table[3] = (Transition) { 1, 'd', 2 };
    table[4] = (Transition) { 1, '.', 3 };
    table[5] = (Transition) { 2, 'd', 2 };
    table[6] = (Transition) { 2, '.', 4 };
    table[7] = (Transition) { 2, 'E', 6 };
    table[8] = (Transition) { 3, 'd', 5 };
    table[9] = (Transition) { 4, 'd', 5 };
    table[10] = (Transition) { 5, 'd', 5 };
    table[11] = (Transition) { 5, 'E', 6 };
    table[12] = (Transition) { 6, 'd', 8 };
    table[13] = (Transition) { 6, 's', 7 };
    table[14] = (Transition) { 7, 'd', 8 };
    table[15] = (Transition) { 8, 'd', 8 };

    int start = 0;
    int m = 3;
    int finStates[3] = { 2, 5, 8 };
    int errCode = 0;
    assert(checkStringForNumber(n, table, m, finStates, start, "123", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "-123", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, ".75", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "-.75", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "12.34", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "0.0001", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "1E5", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "1.2E-3", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "52E+67", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "-12.34E+56", &errCode) == true);
    assert(checkStringForNumber(n, table, m, finStates, start, "0", &errCode) == true);

    printf("--- Positive test passed! ---\n");
}

void negativeTest(void)
{
    printf("--- Start negative tests ---\n");
    int n = 16;
    Transition table[16];

    table[0] = (Transition) { 0, 's', 1 };
    table[1] = (Transition) { 0, 'd', 2 };
    table[2] = (Transition) { 0, '.', 3 };
    table[3] = (Transition) { 1, 'd', 2 };
    table[4] = (Transition) { 1, '.', 3 };
    table[5] = (Transition) { 2, 'd', 2 };
    table[6] = (Transition) { 2, '.', 4 };
    table[7] = (Transition) { 2, 'E', 6 };
    table[8] = (Transition) { 3, 'd', 5 };
    table[9] = (Transition) { 4, 'd', 5 };
    table[10] = (Transition) { 5, 'd', 5 };
    table[11] = (Transition) { 5, 'E', 6 };
    table[12] = (Transition) { 6, 'd', 8 };
    table[13] = (Transition) { 6, 's', 7 };
    table[14] = (Transition) { 7, 'd', 8 };
    table[15] = (Transition) { 8, 'd', 8 };

    int start = 0;
    int m = 3;
    int finStates[3] = { 2, 5, 8 };
    int errCode = 0;
    assert(checkStringForNumber(n, table, m, finStates, start, "12.34.56", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "1E2E3", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "-", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "12.", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, ".", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "E95", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "12E", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, ".E42", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "52E+", &errCode) == false);
    assert(checkStringForNumber(n, table, m, finStates, start, "", &errCode) == false);

    printf("--- Negative tests passed! ---\n");
}

void runTests(void)
{
    printf("--- Start testing! ---\n");
    positiveTest();
    negativeTest();
    printf("--- All tests passed! ---\n");
}