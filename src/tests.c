#include "CSV.h"
#include <assert.h>

int createTestCSV(char filename[], char content[])
{
    FILE* inputFile = fopen(filename, "w");
    if (inputFile == NULL) {
        printf("Ошибка: не удалось создать тестовый CSV файл\n");
        assert(inputFile != NULL);
        return -1;
    }

    fputs(content, inputFile);
    fclose(inputFile);
    return 0;
}

int compareFileWithString(char filename[], char expected[])
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть тестовый CSV файл");
        assert(file != NULL);
        return -1;
    }

    char buffer[1000];
    int len = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[len] = '\0';
    fclose(file);

    int result = (strcmp(buffer, expected) != 0);
    if (result != 0) {
        printf("Ошибка: несоответствие содержимого файла.\n");
        printf("Ожидается:\n%s\n", expected);
        printf("Получено:\n%s\n", buffer);
        assert(result == 0);
    }

    return 0;
}

void testIsNumber(void)
{
    printf("--- Testing isNumber ---\n");

    assert(isNumber("123") == true);
    assert(isNumber("3.14") == true);
    assert(isNumber("-12") == true);
    assert(isNumber("-0.5") == true);
    assert(isNumber("0") == true);

    assert(isNumber("") == false);
    assert(isNumber("abc") == false);
    assert(isNumber("-") == false);
    assert(isNumber("123a45") == false);
    assert(isNumber("12.34.56") == false);

    printf("--- Test isNumber passed! ---\n");
}

void testContainLineBreak(void)
{
    printf("--- Testing containLineBreak ---\n");
    assert(containLineBreak(NULL) == false);
    assert(containLineBreak("") == false);
    assert(containLineBreak("hello\nworld") == true);
    assert(containLineBreak("end\n") == true);
    assert(containLineBreak("no break") == false);
    printf("--- Test containLineBreak passed! ---\n");
}

void testBaseCSV(void)
{
    printf("--- Testing base CSV ---:\n");

    char input[] = "Test field 1,Test field 2\n"
                   "test,123\n"
                   "long string test!,28.7\n"
                   "other text,3\n";

    char expected[] = "+===================+==============+\n"
                      "| Test field 1      | Test field 2 |\n"
                      "+===================+==============+\n"
                      "| test              |          123 |\n"
                      "+-------------------+--------------+\n"
                      "| long string test! |         28.7 |\n"
                      "+-------------------+--------------+\n"
                      "| other text        |            3 |\n"
                      "+-------------------+--------------+\n";

    createTestCSV("test_input.csv", input);

    FILE* inputFile = fopen("test_input.csv", "r");
    if (!input) {
        printf("Не удалось открыть файл\n");
        assert(inputFile != NULL);
    }

    int result = CSV(inputFile, "test_output.txt");

    assert(result == 0);

    compareFileWithString("test_output.txt", expected);

    printf("--- Test base CSV passed! ---\n");
}

void runTests(void)
{
    printf("--- Starting Tests! ---\n");

    testIsNumber();
    testContainLineBreak();
    testBaseCSV();

    printf("--- ALL Tests passed! ---\n");
}