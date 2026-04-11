#include "airports.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* filename = argv[1];

    Node* root = createAVLtree(filename);
    if (root == NULL) {
        printf("Ошибка формирования дерева или пустой файл\n");
        return 1;
    }

    printf("Команды для работы:\n\nfind <код> - Найти название аэропорта по коду IATA\n");
    printf("add <код>:<название> - Добавить новый аэропорт в базу\ndelete <код> - Удалить аэропорт из базы\n");
    printf("save - Сохранить текущее состояние базы обратно в airports.txt\nquit - Завершить работу программы\n\n");

    char input[500];
    char command[10];
    char str[100];
    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);
        char* temp = strchr(input, '\n');
        *temp = '\0';
        if (input[0] == '\0') {
            continue;
        }
        sscanf(input, "%9s", command);
        char* args = strchr(input, ' ');
        if (args) {
            while (*args == ' ')
                args++;
            strcpy(str, args);
            str[sizeof(str) - 1] = '\0';
        } else {
            str[0] = '\0';
        }

        if (!strcmp(command, "find")) {
            find(root, str);
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
            save(root, filename);
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