#include "CSV.h"
#include <ctype.h>
#include <stdlib.h>

#define FILLING_SPACE 1 /* Отступ: по 1 пробелу слева и справа от содержимого ячейки */

bool doesContainLineBreak(const char* str)
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

bool isNumber(char* str)
{
    if (!str) {
        return false;
    }
    int i = 0;
    size_t len = strlen(str);

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

bool printSeparation(FILE* output, int countOfColumn, const int* maxWidth, char c)
{
    if (!output || !maxWidth) {
        return false;
    }
    fputc('+', output);
    for (int i = 0; i < countOfColumn; i++) {
        for (int j = 0; j < maxWidth[i] + 2 * FILLING_SPACE; j++) {
            fputc(c, output);
        }
        fputc('+', output);
    }
    fputc('\n', output);
    return true;
}

bool printHead(char* csvLine, int countOfColumn, const int* maxWidth, FILE* output)
{
    if (!csvLine || !maxWidth || !output) {
        return false;
    }

    if (!printSeparation(output, countOfColumn, maxWidth, '=')) {
        return false;
    }

    size_t len = strlen(csvLine);
    char* copy = malloc(len + 1);
    if (!copy) {
        return false;
    }
    memcpy(copy, csvLine, len + 1);
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

    return printSeparation(output, countOfColumn, maxWidth, '=');
}

bool printBody(char* csvLine, int countOfColumn, const int* maxWidth, FILE* output)
{
    if (!csvLine || !maxWidth || !output) {
        return false;
    }

    size_t len = strlen(csvLine);
    char* copy = malloc(len + 1);
    if (!copy) {
        return false;
    }
    memcpy(copy, csvLine, len + 1);
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

    if (!printSeparation(output, countOfColumn, maxWidth, '-')) {
        return false;
    }
    return true;
}

bool readFullString(FILE* file, char** buffer, int* capacity)
{
    if (!file || !buffer || !capacity) {
        return false;
    }

    if (*buffer == NULL) {
        *capacity = 100;
        *buffer = malloc(*capacity);
        if (!*buffer) {
            return false;
        }
    }

    int position = 0;
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (position + 1 >= *capacity) {
            int newCapacity = *capacity * 2;
            char* tmp = realloc(*buffer, newCapacity);
            if (!tmp) {
                return false; /* При ошибке realloc исходный буфер остаётся валидным */
            }
            *buffer = tmp;
            *capacity = newCapacity;
        }
        (*buffer)[position] = (char)c;
        position++;
    }
    (*buffer)[position] = '\0';
    return (position == 0 && c == EOF) ? false : true;
}

bool parseFirstString(FILE* input, char** currentString, int* bufferCapacity, int* countOfColumn, int** maxWidth, int* maxWidthCapacity)
{
    if (!readFullString(input, currentString, bufferCapacity) || !(*currentString)) {
        return false;
    }

    size_t currentStringLen = strlen(*currentString);
    if (currentStringLen > 0 && (*currentString)[currentStringLen - 1] == '\n') {
        (*currentString)[currentStringLen - 1] = '\0';
    }

    int sizeArrOfWidth = 5;
    *maxWidth = calloc(sizeArrOfWidth, sizeof(int));
    if (!*maxWidth) {
        return false;
    }

    char* token = *currentString;

    while (token) {
        if (sizeArrOfWidth == *countOfColumn) {
            sizeArrOfWidth *= 2;
            int* tmp = realloc(*maxWidth, sizeArrOfWidth * sizeof(int));
            if (!tmp) {
                free(*maxWidth);
                return false;
            }
            *maxWidth = tmp;

            // Обнуляем мусор в новых элементах
            for (int i = *countOfColumn; i < sizeArrOfWidth; i++) {
                (*maxWidth)[i] = 0;
            }
        }

        char* next = strchr(token, ',');
        if (next) {
            *next = '\0';
        }

        size_t temp = strlen(token);
        if (temp > (*maxWidth)[*countOfColumn]) {
            (*maxWidth)[*countOfColumn] = (int)temp;
        }

        (*countOfColumn)++;
        token = next ? next + 1 : NULL;
    }

    *maxWidthCapacity = sizeArrOfWidth;
    return true;
}

bool calculateMaxWidth(FILE* input, char** currentString, int* bufferCapacity, int countOfColumn, int* maxWidth, int maxWidthCapacity)
{
    while (readFullString(input, currentString, bufferCapacity)) {
        size_t currentStringLen = strlen(*currentString);
        if (currentStringLen > 0 && (*currentString)[currentStringLen - 1] == '\n') {
            (*currentString)[currentStringLen - 1] = '\0';
        }

        char* token = *currentString;
        int i = 0;
        while (token && i < countOfColumn) {
            char* next = strchr(token, ',');
            if (next) {
                *next = '\0';
            }

            size_t temp = strlen(token);
            if (temp > (size_t)maxWidth[i]) {
                maxWidth[i] = (int)temp;
            }
            i++;
            token = next ? next + 1 : NULL;
        }
    }
    return true;
}

bool writeFormattedTable(FILE* input, char** currentString, int* bufferCapacity, int countOfColumn, int* maxWidth, const char* nameOfOutputFile)
{
    rewind(input);

    FILE* output = fopen(nameOfOutputFile, "w");
    if (!output) {
        printf("Не удалось открыть файл для записи");
        return false;
    }

    bool isFirstString = true;
    while (readFullString(input, currentString, bufferCapacity)) {
        size_t currentStringLen = strlen(*currentString);
        if (currentStringLen > 0 && (*currentString)[currentStringLen - 1] == '\n') {
            (*currentString)[currentStringLen - 1] = '\0';
        }

        if (isFirstString) {
            if (!printHead(*currentString, countOfColumn, maxWidth, output)) {
                fclose(output);
                return false;
            }
            isFirstString = false;
        } else {
            if (!printBody(*currentString, countOfColumn, maxWidth, output)) {
                fclose(output);
                return false;
            }
        }
    }
    fclose(output);
    return true;
}

bool csv(FILE* input, const char* nameOfOutputFile)
{
    if (!input || !nameOfOutputFile) {
        return false;
    }

    char* currentString = NULL;
    int bufferCapacity = 0;
    int countOfColumn = 0;
    int* maxWidth = NULL;
    int maxWidthCapacity = 0;
    bool result = false;

    // Из первой строки узнаем сколько у нас столбцов и длины полей
    if (!parseFirstString(input, &currentString, &bufferCapacity, &countOfColumn, &maxWidth, &maxWidthCapacity)) {
        free(maxWidth);
        free(currentString);
        return result;
    }

    // Считаем длины полей в остальных строках и оставляем максимальную
    if (!calculateMaxWidth(input, &currentString, &bufferCapacity, countOfColumn, maxWidth, maxWidthCapacity)) {
        free(maxWidth);
        free(currentString);
        return result;
    }

    // проходимся еще раз по файлу для печати
    result = writeFormattedTable(input, &currentString, &bufferCapacity, countOfColumn, maxWidth, nameOfOutputFile);

    free(maxWidth);
    free(currentString);
    return result;
}