#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void printMatrix(int **dist, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("%4s", "INF");
            } else {
                printf("%4d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

void apsp_with_matrix_multiplication(int **graph, int n) {
    int **dist = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (graph[i][j] == 0) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printMatrix(dist, n);

    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
}

int main() {
    int n = 6;
    int graph[6][6] = {
        {0, 3, 0, 0, 0, 0},
        {3, 0, 1, 0, 0, 0},
        {0, 1, 0, 7, 0, 2},
        {0, 0, 7, 0, 2, 3},
        {0, 0, 0, 2, 0, 4},
        {0, 0, 2, 3, 4, 0}
    };

    int **graph_ptr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph_ptr[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            graph_ptr[i][j] = graph[i][j];
        }
    }

    printf("The All-Pairs Shortest Paths distance matrix is:\n");
    apsp_with_matrix_multiplication(graph_ptr, n);

    for (int i = 0; i < n; i++) {
        free(graph_ptr[i]);
    }
    free(graph_ptr);

    return 0;
}
