#include "dfa.h"
#include <ctype.h>

bool dfa(int n, Transition* table, int m, int* finStates, int start, char* input, int* errCode)
{

    int currState = start;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (c != '.' && c != 'E' && c != '-' && c != '+' && !isdigit(c)) {
            *errCode = 1;
            return false;
        }

        bool found = false;

        for (int j = 0; j < n; j++) {
            bool match = false;
            if (table[j].symbol == c) {
                match = true;
            } else if (table[j].symbol == 'd' && isdigit(c)) {
                match = true;
            } else if (table[j].symbol == 's' && (c == '+' || c == '-')) {
                match = true;
            }

            if (match && table[j].fromState == currState) {
                found = true;
                currState = table[j].toState;
                break;
            }
        }

        if (!found) {
            *errCode = 2;
            return false;
        }
    }

    for (int i = 0; i < m; i++) {
        if (currState == finStates[i]) {
            return true;
        }
    }

    *errCode = 3;
    return false;
}