#include "AVLtree.h"
#include "tests.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SIZE_OF_STR 100

int main(int argc, char* argv[])
{
    if ((argc > 1) && (strcmp(argv[1], "--test") == 0)) {
        runTests();
        return 0;
    }

    char* fileName = argv[1];

    Node* root = createAVLtree(fileName);
    if (root == NULL) {
        printf("Ошибка формирования дерева или пустой файл\n");
        return 1;
    }

    printf("Команды для работы:\n\nfind <код> - Найти название аэропорта по коду IATA\n");
    printf("add <код>:<название> - Добавить новый аэропорт в базу\ndelete <код> - Удалить аэропорт из базы\n");
    printf("save - Сохранить текущее состояние базы обратно в airports.txt\nquit - Завершить работу программы\n\n");

    char input[500];
    char command[10];
    char str[SIZE_OF_STR];

    while (true) {
        printf(">> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        char* temp = strchr(input, '\n');
        if (temp)
            *temp = '\0';

        if (input[0] == '\0') {
            continue;
        }

        sscanf(input, "%9s", command);
        char* args = strchr(input, ' ');
        if (args) {
            while (*args == ' ')
                args++;
            strncpy(str, args, SIZE_OF_STR - 1);
            str[SIZE_OF_STR - 1] = '\0';
        } else {
            str[0] = '\0';
        }

        if (!strcmp(command, "find")) {
            Node* found = find(root, str);
            if (found) {
                printf("%s -> %s.\n", found->code, found->name);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", str);
            }
        }

        else if (!strcmp(command, "add")) {
            if (strchr(str, ':') == NULL) {
                printf("Введено некорректное название, должен быть символ-разделитель ':'\n");
            } else {
                root = add(root, str);
            }
        }

        else if (!strcmp(command, "delete")) {
            root = deleteNode(root, str);
        }

        else if (!strcmp(command, "save")) {
            save(root, fileName);
            printf("Состояние базы сохранено\n");
        }

        else if (!strcmp(command, "quit")) {
            break;
        }

        else {
            printf("Неверная команда\n");
        }
    }

    freeTree(root);
    return 0;
}