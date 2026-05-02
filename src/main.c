#include "states.h"
#include "heap.h"
#include <stdlib.h>

typedef struct Edge {
    int to;
    int len;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge** graph;
} Graph;

typedef struct HeapNode {
    int city;
    int dist;
} HeapNode;

typedef struct MinHeap {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

int main(void)
{
    int countOfCities;
    int countOfRoads;
    int countOfStates;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    fscanf(file, "%d %d", &countOfCities, &countOfRoads);

    int* ownerOfCity = calloc(countOfCities, sizeof(int));
    if (ownerOfCity == NULL) {
        fclose(file);
        return 1;
    }

    Graph* graph = initGraph(countOfCities);
    if (!graph) {
        free(ownerOfCity);
        return 1;
    }
    if(!readEdge(file, graph, countOfRoads)) {
        free(ownerOfCity);
        freeGraph(graph, countOfCities);
        fclose(file);
        return 1;
    }

    fscanf(file, "%d", &countOfStates);
    int* capitals = malloc(countOfStates * sizeof(int));
    if (!capitals) {
        free(ownerOfCity);
        freeGraph(graph, countOfCities);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < countOfStates; i++) {
        fscanf(file, "%d", &capitals[i]);
        capitals[i]--;
    }
    fclose(file);

    MinHeap** heaps = malloc(countOfStates * sizeof(MinHeap*)); 
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

    int captured = 0;
    for (int i = 0; i < countOfStates; i++) {
        int cap = capitals[i];
        ownerOfCity[cap] = i + 1;

        captured++;

        Edge* edge = graph->graph[cap]; // берем список городов куда можно попасть из столицы
        for (edge; edge != NULL; edge = edge->next) {
            heapPush(heaps[i], edge->to, edge->len);
        }
    }

    while (captured < countOfCities) {
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
                captured++;

                Edge* edge = graph->graph[candidate.city];
                for (edge; edge != NULL; edge = edge->next) {
                    heapPush(heaps[i], edge->to, edge->len);
                }
            }
        }
    }

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

    for (int i = 0; i < countOfStates; i++) {
        freeHeap(heaps[i]);
    }
    free(heaps);
    free(capitals);
    free(ownerOfCity);
    freeGraph(graph, countOfCities);
    return 0;
}