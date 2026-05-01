#pragma once

#include <stdbool.h>

// Структура перехода для ДКА
typedef struct Transition {
    // Из какого состояния
    int fromState;
    // Символ перехода ('d' - цифра, 's' - знак)
    char symbol;
    // В какое состояние
    int toState;
} Transition;

// Функция, симулирующая работу ДКА и проверяющая является ли строка числом
bool checkStringForNumber(int n, Transition* table, int m, const int* finStates, int start, const char* input, int* errCode);

void runTests(void);