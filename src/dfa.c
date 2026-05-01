#include "dfa.h"

#include <ctype.h>

bool checkStringForNumber(int n, Transition* table, int m, const int* finStates, int start, const char* input, int* errCode)
{
    int currentState = start;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        bool found = false;

        for (int j = 0; j < n; j++) {
            bool match = false;
            if ((table[j].symbol == c) || (table[j].symbol == 'd' && isdigit(c)) || (table[j].symbol == 's' && (c == '+' || c == '-'))) {
                match = true;
            }

            if (match && table[j].fromState == currentState) {
                found = true;
                currentState = table[j].toState;
                break;
            }
        }

        if (!found) {
            *errCode = 1;
            return false;
        }
    }

    for (int i = 0; i < m; i++) {
        if (currentState == finStates[i]) {
            return true;
        }
    }

    *errCode = 2;
    return false;
}