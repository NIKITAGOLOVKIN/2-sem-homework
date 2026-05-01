#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Проверка наличия переноса строки
bool containLineBreak(const char* str);

// Проверка, является ли строка числом
bool isNumber(char* str);

// Отрисовка разделительной линии
bool printSeparation(FILE* output, int countOfColumn, int* maxWidth, char c);

// Вывод заголовка
bool printHead(char* str, int countOfColumn, int* maxWidth, FILE* output);

// Вывод тела таблицы
bool printBody(char* str, int countOfColumn, int* maxWidth, FILE* output);

bool readFullString(FILE* file, char** buffer, int* capacity);

bool CSV(FILE* input, const char* nameOfOutputFile);

void runTests(void);