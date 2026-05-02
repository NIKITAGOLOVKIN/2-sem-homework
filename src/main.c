#include "CSV.h"
#include "tests.h"

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

    if (!csv(input, nameOfOutputFile)) {
        printf("Ошибка в работе CSV");
        fclose(input);
        return -1;
    }

    fclose(input);
    return 0;
}