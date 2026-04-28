#include "CSV.h"
#include <ctype.h>
#include <stdlib.h>

#define FILLINGSPACE 1 /* Отступ: по 1 пробелу слева и справа от содержимого ячейки */

/* Проверка наличия переноса строки */
bool containLineBreak(const char* str)
{
    if (!str) {
        return false;
    }
    for (char i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            return true;
        }
    }
    return false;
}

/* Проверка, является ли строка числом */
bool isNumber(char* str)
{
    if (!str) {
        return false;
    }
    int i = 0;
    const int len = strlen(str);

    if (str[i] == '-') {
        i++;
        if (i >= len)
            return false;
    }

    bool hasDigit = false;
    bool hasDot = false;

    for (; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            hasDigit = true;
        } else if (str[i] == '.') {
            if (hasDot) {
                return false;
            }
            hasDot = true;
        } else {
            return false;
        }
    }
    return hasDigit;
}

/* Отрисовка разделительной линии */
void printSeparation(FILE* output, int countOfColumn, int* maxWidth, char c)
{
    if (!output || !maxWidth) {
        return;
    }
    fputc('+', output);
    for (int i = 0; i < countOfColumn; i++) {
        for (int j = 0; j < maxWidth[i] + 2 * FILLINGSPACE; j++) {
            fputc(c, output);
        }
        fputc('+', output);
    }
    fputc('\n', output);
}

/* Вывод заголовка */
void printHead(char* str, int countOfColumn, int* maxWidth, FILE* output)
{
    if (!str || !maxWidth || !output) {
        return;
    }

    printSeparation(output, countOfColumn, maxWidth, '=');

    int len = strlen(str);
    char* copy = malloc(len + 1);
    if (!copy) {
        return;
    }
    strcpy(copy, str);
    char* token = copy;
    char* next;
    int countOfSpace = 0;
    int i = 0;

    while (token && i < countOfColumn) {
        next = strchr(token, ',');
        if (next) {
            *next = '\0';
        }

        fprintf(output, "| %-*s ", maxWidth[i], token);

        i++;
        token = next ? next + 1 : NULL;
    }

    for (; i < countOfColumn; i++) {
        fprintf(output, "| %-*s ", maxWidth[i], "");
    }
    fputc('|', output);
    fputc('\n', output);
    free(copy);

    printSeparation(output, countOfColumn, maxWidth, '=');
}

/* Вывод тела таблицы */
void printBody(char* str, int countOfColumn, int* maxWidth, FILE* output)
{
    if (!str || !maxWidth || !output) {
        return;
    }

    int len = strlen(str);
    char* copy = malloc(len + 1);
    if (!copy) {
        return;
    }
    strcpy(copy, str);
    char* token = copy;
    char* next;
    int countOfSpace = 0;
    int i = 0;

    while (token && i < countOfColumn) {
        next = strchr(token, ',');
        if (next) {
            *next = '\0';
        }

        if (isNumber(token)) {
            fprintf(output, "| %*s ", maxWidth[i], token);
        } else {
            fprintf(output, "| %-*s ", maxWidth[i], token);
        }

        i++;
        token = next ? next + 1 : NULL;
    }
    fputc('|', output);
    fputc('\n', output);
    free(copy);

    printSeparation(output, countOfColumn, maxWidth, '-');
}

int readFullString(FILE* file, char** buffer, int* capacity)
{
    if (!file || !buffer || !capacity) {
        return 0;
    }

    if (*buffer == NULL) {
        *capacity = 100;
        *buffer = malloc(*capacity);
        if (!*buffer) {
            return 0;
        }
    }

    int position = 0;
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (position + 1 >= *capacity) {
            int newCapacity = *capacity * 2;
            char* tmp = realloc(*buffer, newCapacity);
            if (!tmp) {
                return 0; /* При ошибке realloc исходный буфер остаётся валидным */
            }
            *buffer = tmp;
            *capacity = newCapacity;
        }
        (*buffer)[position] = (char)c;
        position++;
    }
    (*buffer)[position] = '\0';
    return (position == 0 && c == EOF) ? 0 : 1;
}

int CSV(FILE* input, const char* nameOfOutputFile)
{
    if (!input || !nameOfOutputFile) {
        return -1;
    }

    /* Из первой строки узнаем сколько у нас столбцов и длины полей */
    char* currStr = NULL;
    int bufferCapacity = 0;

    if (readFullString(input, &currStr, &bufferCapacity) == 0 || !currStr) {
        free(currStr);
        return -1;
    }

    int currStrLen = strlen(currStr);
    if (currStrLen > 0 && currStr[currStrLen - 1] == '\n') {
        currStr[currStrLen - 1] = '\0';
    }

    int sizeArrOfWidth = 5;
    int* maxWidth = calloc(sizeArrOfWidth, sizeof(int));
    if (!maxWidth) {
        printf("calloc failed");
        free(currStr);
        return -1;
    }

    int countOfColumn = 0;
    char* token = currStr;
    char* next;

    while (token) {
        if (sizeArrOfWidth == countOfColumn) {
            sizeArrOfWidth *= 2;
            int* tmp = realloc(maxWidth, sizeArrOfWidth * sizeof(int));
            if (!tmp) {
                free(maxWidth);
                free(currStr);
                return -1;
            }
            maxWidth = tmp;

            /* Обнуляем мусор в новых элементах */
            for (int k = countOfColumn; k < sizeArrOfWidth; k++) {
                maxWidth[k] = 0;
            }
        }

        next = strchr(token, ',');
        if (next) {
            *next = '\0';
        }

        int temp = strlen(token);
        if (temp > maxWidth[countOfColumn]) {
            maxWidth[countOfColumn] = temp;
        }

        countOfColumn++;
        token = next ? next + 1 : NULL;
    }

    /* Считаем длины полей в остальных строках и оставляем максимальную */

    bufferCapacity = 10;
    currStr = realloc(currStr, bufferCapacity);
    if (!currStr) {
        free(maxWidth);
        return -1;
    }

    while (readFullString(input, &currStr, &bufferCapacity)) {
        int currStrLen = strlen(currStr);
        if (currStrLen > 0 && currStr[currStrLen - 1] == '\n') {
            currStr[currStrLen - 1] = '\0';
        }

        token = currStr;
        int i = 0;
        while (token && i < countOfColumn) {
            next = strchr(token, ',');
            if (next) {
                *next = '\0';
            }

            int temp = strlen(token);
            if (temp > maxWidth[i]) {
                maxWidth[i] = temp;
            }
            i++;
            token = next ? next + 1 : NULL;
        }
    }

    /* проходимся еще раз по файлу для печати */
    rewind(input);

    FILE* output = fopen(nameOfOutputFile, "w");
    if (!output) {
        printf("Не удалось открыть файл для записи");
        free(currStr);
        free(maxWidth);
        return -1;
    }

    bool firstString = true;
    while (readFullString(input, &currStr, &bufferCapacity)) {
        int currStrLen = strlen(currStr);
        if (currStrLen > 0 && currStr[currStrLen - 1] == '\n') {
            currStr[currStrLen - 1] = '\0';
        }

        if (firstString) {
            printHead(currStr, countOfColumn, maxWidth, output);
            firstString = false;
        } else {
            printBody(currStr, countOfColumn, maxWidth, output);
        }
    }

    free(maxWidth);
    free(currStr);
    fclose(output);
    return 0;
}