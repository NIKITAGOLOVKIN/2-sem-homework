#include "heap.h"
#include "states.h"
#include <stdlib.h>

bool readInput(const char* filename, const int* countOfCities, const int* countOfRoads, Graph** graph, int** ownerOfCity, const int* countOfStates, int** capitals)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

    fscanf(file, "%d %d", &(*countOfCities), &(*countOfRoads));

    *ownerOfCity = calloc(*countOfCities, sizeof(int));
    if (*ownerOfCity == NULL) {
        fclose(file);
        return false;
    }

    *graph = initGraph(*countOfCities);
    if (!*graph) {
        free(*ownerOfCity);
        return false;
    }
    if (!readEdge(file, *graph, *countOfRoads)) {
        free(*ownerOfCity);
        freeGraph(*graph, *countOfCities);
        fclose(file);
        return false;
    }

    fscanf(file, "%d", &(*countOfStates));
    *capitals = malloc(*countOfStates * sizeof(int));
    if (!*capitals) {
        free(*ownerOfCity);
        freeGraph(*graph, *countOfCities);
        fclose(file);
        return false;
    }

    for (int i = 0; i < *countOfStates; i++) {
        fscanf(file, "%d", &((*capitals)[i]));
        ((*capitals)[i])--;
    }
    fclose(file);
    return true;
}

bool initializationOfCapitals(int* ownerOfCity, MinHeap** heaps, Graph* graph, const int* capitals, int countOfStates, int* captured)
{
    *captured = 0;
    for (int i = 0; i < countOfStates; i++) {
        int cap = capitals[i];
        ownerOfCity[cap] = i + 1;

        (*captured)++;

        Edge* edge = graph->graph[cap]; // берем список городов куда можно попасть из столицы
        for (; edge != NULL; edge = edge->next) {
            if (!heapPush(heaps[i], edge->to, edge->len)) {
                return false;
            }
        }
    }
    return true;
}

void captureOfCities(int* ownerOfCity, MinHeap** heaps, Graph* graph, int countOfCities, int countOfStates, int* captured)
{
    while (*captured < countOfCities) {
        for (int i = 0; i < countOfStates; i++) {
            int currentState = i + 1;
            MinHeap* heap = heaps[i];
            bool found = false;
            HeapNode candidate;

            while (heap->size > 0) {
                heapPop(heap, &candidate);
                if (ownerOfCity[candidate.city] == 0) {
                    found = true;
                    break;
                }
            }

            if (found) {
                ownerOfCity[candidate.city] = currentState;
                (*captured)++;

                Edge* edge = graph->graph[candidate.city];
                for (; edge != NULL; edge = edge->next) {
                    heapPush(heaps[i], edge->to, edge->len);
                }
            }
        }
    }
}

void printResults(const int* ownerOfCity, int countOfCities, int countOfStates)
{
    printf("Результат распределения:\n");
    for (int i = 1; i <= countOfStates; i++) {
        printf("Государство %d:", i);
        for (int j = 0; j < countOfCities; j++) {
            if (ownerOfCity[j] == i) {
                printf(" %d", j + 1);
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int countOfCities;
    int countOfRoads;
    int countOfStates;
    Graph* graph = NULL;
    int* ownerOfCity = NULL;
    int* capitals = NULL;
    MinHeap** heaps = NULL;
    int captured;

    if (!readInput("input.txt", &countOfCities, &countOfRoads, &graph, &ownerOfCity, &countOfStates, &capitals)) {
        return 1;
    }

    heaps = calloc(countOfStates, sizeof(MinHeap*));
    if (!heaps) {
        free(ownerOfCity);
        free(capitals);
        freeGraph(graph, countOfCities);
        return 1;
    }

    for (int i = 0; i < countOfStates; i++) {
        heaps[i] = initMinHeap();
        if (!(heaps[i])) {
            for (int j = 0; j < countOfStates; j++) {
                freeHeap(heaps[j]);
            }
            free(heaps);
            free(capitals);
            free(ownerOfCity);
            freeGraph(graph, countOfCities);
            return 1;
        }
    }

    if (!initializationOfCapitals(ownerOfCity, heaps, graph, capitals, countOfStates, &captured)) {
        for (int j = 0; j < countOfStates; j++) {
            freeHeap(heaps[j]);
        }
        free(heaps);
        free(capitals);
        free(ownerOfCity);
        freeGraph(graph, countOfCities);
        return 1;
    }

    captureOfCities(ownerOfCity, heaps, graph, countOfCities, countOfStates, &captured);
    printResults(ownerOfCity, countOfCities, countOfStates);

    for (int i = 0; i < countOfStates; i++) {
        freeHeap(heaps[i]);
    }
    free(heaps);
    free(capitals);
    free(ownerOfCity);
    freeGraph(graph, countOfCities);
    return 0;
}