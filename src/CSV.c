#include "CSV.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool isFullString(char* str)
{
    for (char i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            return true;
        }
    }
    return false;
}

bool isNumber(char* str)
{
    int i = 0;
    int len = strlen(str);

    if (str[i] == '-') {
        i++;
        if (i >= len)
            return false;
    }

    bool hasDigit = false;
    bool hasDot = false;

    for (; i < len; i++) {
        if (isdigit(str[i])) {
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

void printHead(char* str, int countOfColumn, int* maxWidth, FILE* output)
{
    fputc('+', output);
    char* token = NULL;
    for (int i = 0; i < countOfColumn; i++) {
        for (int j = 0; j < maxWidth[i] + 2; j++) {
            fputc('=', output);
        }
        fputc('+', output);
    }
    fputc('\n', output);

    int countOfSpace;
    token = strtok(str, ",");
    int i = 0;
    while (token && i < countOfColumn) {
        if (isNumber(token)) {
            fputc('|', output);
            countOfSpace = maxWidth[i] - strlen(token);
            for (int j = 0; j < countOfSpace; ++j) {
                fputc(' ', output);
            }
            fputc(' ', output);
            fputs(token, output);
            fputc(' ', output);
        } else {
            fputc('|', output);
            fputc(' ', output);
            fputs(token, output);
            fputc(' ', output);
            countOfSpace = maxWidth[i] - strlen(token);
            for (int j = 0; j < countOfSpace; ++j) {
                fputc(' ', output);
            }
        }
        i++;
        token = strtok(NULL, ",");
    }
    fputc('|', output);
    fputc('\n', output);

    fputc('+', output);
    for (int i = 0; i < countOfColumn; i++) {
        for (int j = 0; j < maxWidth[i] + 2; j++) {
            fputc('=', output);
        }
        fputc('+', output);
    }
    fputc('\n', output);
}

void printBody(char* str, int countOfColumn, int* maxWidth, FILE* output)
{

    int countOfSpace;
    char* token = strtok(str, ",");
    int i = 0;
    while (token && i < countOfColumn) {
        if (isNumber(token)) {
            fputc('|', output);
            countOfSpace = maxWidth[i] - strlen(token);
            for (int j = 0; j < countOfSpace; ++j) {
                fputc(' ', output);
            }
            fputc(' ', output);
            fputs(token, output);
            fputc(' ', output);
        } else {
            fputc('|', output);
            fputc(' ', output);
            fputs(token, output);
            fputc(' ', output);
            countOfSpace = maxWidth[i] - strlen(token);
            for (int j = 0; j < countOfSpace; ++j) {
                fputc(' ', output);
            }
        }
        i++;
        token = strtok(NULL, ",");
    }
    fputc('|', output);
    fputc('\n', output);

    fputc('+', output);
    for (int i = 0; i < countOfColumn; i++) {
        for (int j = 0; j < maxWidth[i] + 2; j++) {
            fputc('-', output);
        }
        fputc('+', output);
    }
    fputc('\n', output);
}

FILE* CSV(FILE* input)
{
/*-------------------------Из первой строки узнаем сколько у нас столбцов и плюсом считаем длины полей-----------------------------*/

    int size = 5;
    char* currStr = malloc(size);
    fgets(currStr, size, input);
    int totalRead = strlen(currStr);

    while (!isFullString(currStr)) {
        size *= 2;
        currStr = realloc(currStr, size);
        fgets(currStr + totalRead, size - totalRead, input);
        totalRead += strlen(currStr + totalRead);
    }
    currStr[strcspn(currStr, "\n")] = '\0';

    size = 5;
    int* maxWidth = calloc(size, sizeof(char));
    int countOfColumn = 0;
    char* token = strtok(currStr, ",");
    while (token) {
        if (size == countOfColumn) {
            size *= 2;
            maxWidth = realloc(maxWidth, size);
        }
        maxWidth[countOfColumn] = ((maxWidth[countOfColumn]) > (strlen(token)) ? (maxWidth[countOfColumn]) : (strlen(token)));
        countOfColumn++;
        token = strtok(NULL, ",");
    }

/*-----------------------------Считаем длины полей в остальных строках и оставляем максимальную-----------------------------------------*/

    size = 10;
    currStr = realloc(currStr, size);
    int i;

    while (fgets(currStr, size, input)) {

        totalRead = strlen(currStr);
        while (!isFullString(currStr) && !feof(input)) {
            size *= 2;
            currStr = realloc(currStr, size);
            fgets(currStr + totalRead, size - totalRead, input);
            totalRead += strlen(currStr + totalRead);
        }
        currStr[strcspn(currStr, "\n")] = '\0';

        token = strtok(currStr, ",");
        i = 0;
        while (token && (i < countOfColumn)) {
            maxWidth[i] = ((maxWidth[i]) > (strlen(token)) ? (maxWidth[i]) : (strlen(token)));
            i++;
            token = strtok(NULL, ",");
        }
    }

/*------------------------------------------------проходимся еще раз по файлу для печати----------------------------------------------*/
    rewind(input);

    FILE* output = fopen("output.txt", "w");

    currStr = realloc(currStr, size);
    bool firstString = true;
    while (fgets(currStr, size, input)) {

        totalRead = strlen(currStr);
        while (!isFullString(currStr) && !feof(input)) {
            size *= 2;
            currStr = realloc(currStr, size);
            fgets(currStr + totalRead, size - totalRead, input);
            totalRead += strlen(currStr + totalRead);
        }
        currStr[strcspn(currStr, "\n")] = '\0';

        if (firstString) {
            printHead(currStr, countOfColumn, maxWidth, output);
            firstString = false;
        } else {
            printBody(currStr, countOfColumn, maxWidth, output);
        }
    }

    free(maxWidth);
    free(token);
    free(currStr);
    fclose(output);
}