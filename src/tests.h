#pragma once

// Создание файла CSV для тестов
int createTestCSV(char filename[], char content[]);

// Сравниваем то что в текстовом файле с ожидаемой строкой
int compareFileWithString(char filename[], char expected[]);

// Тест является ли строка числом
void testIsNumber(void);

// Проверка содержания символа конца строки
void testContainLineBreak(void);

// Тест работы утилиты CSV
void testBaseCSV(void);

// Тест работы утилиты CSV с пустыми полями
void testEmptyFields(void);

// Тест выравнивания
void testAlignment(void);

// Запуск всех тестов
void runTests(void);