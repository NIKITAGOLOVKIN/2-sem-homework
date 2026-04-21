#include "dfa.h"

#include <stdio.h>
#include <string.h>

int main()
{
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

    char input[100];
    printf("Введите строку\n");
    printf(">> ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char* temp = strchr(input, '\n');
        if (temp) {
            *temp = '\0';
        }
    }

    int errCode = 0;
    bool isNumber = dfa(n, &table, m, &finStates, start, &input, &errCode);

    if (isNumber) {
        printf("Это число!\n");
    } else {
        printf("Это не число :(\n");
        if (errCode == 1)
            printf("Ошибка: символ не из алфавита ДКА.\n");
        else if (errCode == 2)
            printf("Ошибка: нет перехода.\n");
        else if (errCode == 3)
            printf("Ошибка: число не завершено (нет цифры после точки/E).\n");
    }

    return 0;
}