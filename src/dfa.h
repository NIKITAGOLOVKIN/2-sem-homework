#include <stdbool.h>
#include <stdlib.h>

typedef struct Transition {
    int fromState; /* Из какого состояния */
    char symbol; /* Символ перехода ('d' - цифра, 's' - знак) */
    int toState; /* В какое состояние */
} Transition;

bool dfa(int n, Transition* table, int m, int* finStates, int start, char* input, int* errCode);