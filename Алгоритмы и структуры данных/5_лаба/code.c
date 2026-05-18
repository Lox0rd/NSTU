#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

//Структура для представления ребра
typedef struct Edge {
    int to;        //номер вершины, куда идёт ребро
    int weight;    //метка (вес) ребра
    struct Edge* next; //указатель на следующее ребро
} Edge;

//Массив списков смежности (иерархический список)
Edge* graph[MAX_VERTICES] = {NULL};
int numVer = 0;

//Функция для добавления ребра в граф
void addEdge(int from, int to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from];
    graph[from] = newEdge;
}

//Чтение матрицы смежности из файла
int readAdjacencyMatrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return -1;
    }

    //Читаем количество вершин
    fscanf(file, "%d", &numVer);

    //Читаем матрицу смежности
    for (int i = 0; i < numVer; i++) {
        for (int j = 0; j < numVer; j++) {
            int weight;
            fscanf(file, "%d", &weight);

            //Если есть ребро
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

    //Проходим по всем вершинам
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

    //Выводим результаты
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
void findShortestPath(int start, int end) {
    int dist[MAX_VERTICES];     
    int prev[MAX_VERTICES];     
    int visited[MAX_VERTICES] = {0}; 

    for (int i = 0; i < numVer; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < numVer - 1; count++) {
        int minDist = INT_MAX;
        int u = -1;

        for (int i = 0; i < numVer; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        Edge* current = graph[u];
        while (current != NULL) {
            int v = current->to;
            int weight = current->weight;

            if (!visited[v] && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            current = current->next;
        }
    }

    //Вывод результата
    if (dist[end] == INT_MAX) {
        printf("Путь от вершины %d до вершины %d не существует\n", start, end);
    } else {
        printf("Кратчайшее расстояние от %d до %d: %d\n", start, end, dist[end]);

        printf("Путь: ");
        int path[MAX_VERTICES];
        int pathLength = 0;
        int current = end;

        while (current != -1) {
            path[pathLength++] = current;
            current = prev[current];
        }

        //Выводим путь
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
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

    int startVertex = 0;  //начальная вершина
    int endVertex = 3;    //конечная вершина

    printf("\nПоиск кратчайшего пути от вершины %d до вершины %d:\n", startVertex, endVertex);
    findShortestPath(startVertex, endVertex);

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
