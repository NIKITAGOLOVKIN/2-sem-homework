#include "CSV.h"

int main(int argc, char* argv[])
{
    if ((argc > 1) && (strcmp(argv[1], "--test") == 0)) {
        runTests();
        return 0;
    }

    const char* nameOfInputFile = "input.csv";
    const char* nameOfOutputFile = "output.txt";

    FILE* input = fopen(nameOfInputFile, "r");
    if (!input) {
        printf("Не удалось открыть файл\n");
        return 1;
    }

    int result = CSV(input, nameOfOutputFile);
    if (result != 0) {
        printf("Операция CSV завершилась с кодом %d\n", result);
        fclose(input);
        return -1;
    }

    fclose(input);
    return 0;
}