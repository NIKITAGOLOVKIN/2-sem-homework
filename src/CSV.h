#pragma once

#include <stdbool.h>
#include <stdio.h>

bool containLineBreak(const char* str);

bool isNumber(char* str);

void printSeparation(FILE* output, int countOfColumn, int* maxWidth, char c);

void printHead(char* str, int countOfColumn, int* maxWidth, FILE* output);

void printBody(char* str, int countOfColumn, int* maxWidth, FILE* output);

int readFullString(FILE* file, char** buffer, int* capacity);

int CSV(FILE* input, const char* nameOfOutputFile);