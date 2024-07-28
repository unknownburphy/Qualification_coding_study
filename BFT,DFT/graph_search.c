#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
};

void initGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

void _DFS(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d->", vertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            _DFS(graph, i, visited);
        }
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    _DFS(graph, startVertex, visited);
}


void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d->", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}


int main() {
    struct Graph graph;
    initGraph(&graph, 5);

    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 1, 4);

    printf("BFS from 0:");
    BFS(&graph, 0);
    printf("\n");
    printf("DFS from 0:");
    DFS(&graph, 0);
    printf("\n");
    return 0;
}

