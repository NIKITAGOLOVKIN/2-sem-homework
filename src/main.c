#include "states.h"

int main(void)
{
    int n;
    int m;
    int k;

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    fscanf(file, "%d %d", &n, &m);

    int* ownerOfCity = calloc(n, sizeof(int));
    if (ownerOfCity == NULL) {
        fclose(file);
        return 1;
    }

    Graph* graph = initGraph(n);
    getEdge(file, graph, m);

    fscanf(file, "%d", &k);
    int* capitals = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        fscanf(file, "%d", &capitals[i]);
        capitals[i]--;
    }
    fclose(file);

    MinHeap** heaps = malloc(k * sizeof(MinHeap*));
    for (int i = 0; i < k; i++) {
        heaps[i] = initMinHeap();
    }

    int captured = 0;
    for (int i = 0; i < k; i++) {
        int cap = capitals[i];
        ownerOfCity[cap] = i + 1;

        captured++;

        Edge* edge = graph->graph[cap]; // берем список городов куда можно попасть из столицы
        for (edge; edge != NULL; edge = edge->next) {
            heapPush(heaps[i], edge->to, edge->len);
        }
    }

    while (captured < n) {
        for (int i = 0; i < k; i++) {
            int currState = i + 1;
            MinHeap* heap = heaps[i];
            int found = 0;
            HeapNode candidate;

            while (heap->size > 0) {
                heapPop(heap, &candidate);
                if (ownerOfCity[candidate.city] == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                ownerOfCity[candidate.city] = currState;
                captured++;

                Edge* edge = graph->graph[candidate.city];
                for (edge; edge != NULL; edge = edge->next) {
                    heapPush(heaps[i], edge->to, edge->len);
                }
            }
        }
    }

    printf("Результат распределения:\n");
    for (int i = 1; i <= k; i++) {
        printf("Государство %d:", i);
        for (int j = 0; j < n; j++) {
            if (ownerOfCity[j] == i) {
                printf(" %d", j + 1);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < k; i++) {
        freeHeap(heaps[i]);
    }
    free(heaps);
    free(capitals);
    free(ownerOfCity);
    freeGraph(graph, n);
    return 0;
}