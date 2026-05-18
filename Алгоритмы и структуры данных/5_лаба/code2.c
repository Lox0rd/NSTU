#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct Edge {
    int to;       
    int weight;   
    struct Edge* next; 
} Edge;

Edge* graph[MAX_VERTICES] = {NULL};
int numVer = 0;

void addEdge(int from, int to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from];
    graph[from] = newEdge;
}

int readAdjacencyMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return -1;
    }

    fscanf(file, "%d", &numVer);

    for (int i = 0; i < numVer; i++) {
        for (int j = 0; j < numVer; j++) {
            int weight;
            fscanf(file, "%d", &weight);

            if (weight != 0 && weight != INT_MAX) {
                addEdge(i, j, weight);
            }
        }
    }

    fclose(file);
    return 0;
}
void printEdges() {
    int fromArray[MAX_VERTICES * MAX_VERTICES];
    int toArray[MAX_VERTICES * MAX_VERTICES];
    int weightArray[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;

    for (int i = 0; i < numVer; i++) {
        Edge* current = graph[i];

        while (current != NULL) {
            fromArray[edgeCount] = i;
            toArray[edgeCount] = current->to;
            weightArray[edgeCount] = current->weight;
            edgeCount++;
            current = current->next;
        }
    }

    printf("Массив 'откуда': ");
    for (int i = 0; i < edgeCount; i++) {
        printf("%d ", fromArray[i]);
    }
    printf("\n");

    printf("Массив 'куда': ");
    for (int i = 0; i < edgeCount; i++) {
        printf("%d ", toArray[i]);
    }
    printf("\n");

    printf("Массив 'метка': ");
    for (int i = 0; i < edgeCount; i++) {
        printf("%d ", weightArray[i]);
    }
    printf("\n");
}

int main() {
    const char* filename = "matrix.txt";

    if (readAdjacencyMatrix(filename) != 0) {
        printf("Ошибка чтения файла");
        return 1;
    }

    printf("Граф создан из матрицы смежности.\n");

    printf("\nРёбра графа:\n");
    printEdges();

    //Освобождение памяти
    for (int i = 0; i < numVer; i++) {
        Edge* current = graph[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
