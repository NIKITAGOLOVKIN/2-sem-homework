#pragma once
#include <stdbool.h>
#include <stdio.h>

bool isFullString(char* str);

bool isNumber(char* str);

void printHead(char* str, int countOfColumn, int* maxWidth, FILE* output);

void printBody(char* str, int countOfColumn, int* maxWidth, FILE* output);

FILE* CSV(FILE* input);