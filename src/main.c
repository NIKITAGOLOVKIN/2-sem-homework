#include "CSV.h"

int main(void)
{
    FILE* input = fopen("input.csv", "r");
    if (!input) {
        printf("file not found\n");
        return 1;
    }

   CSV(input);

    fclose(input);
    return 0;
}