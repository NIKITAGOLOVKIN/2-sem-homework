#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Проверка наличия переноса строки
bool containLineBreak(const char* str);

// Проверка, является ли строка числом
bool isNumber(char* str);

// Отрисовка разделительной линии
bool printSeparation(FILE* output, int countOfColumn, const int* maxWidth, char c);

// Вывод заголовка
bool printHead(char* str, int countOfColumn, const int* maxWidth, FILE* output);

// Вывод тела таблицы
bool printBody(char* str, int countOfColumn, const int* maxWidth, FILE* output);

bool readFullString(FILE* file, char** buffer, int* capacity);

bool csv(FILE* input, const char* nameOfOutputFile);

void runTests(void);