#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

#define INF INT_MAX

void printMatrix(const vector<vector<int>>& dist) {
    for (const auto& row : dist) {
        for (const auto& elem : row) {
            if (elem == INF) {
                cout << "INF ";
            } else {
                cout << elem << " ";
            }
        }
        cout << endl;
    }
}

void apsp_with_matrix_multiplication(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INF;
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

    printMatrix(dist);
}

int main() {
    vector<vector<int>> graph = {
        {0, 3, 0, 0, 0, 0},
        {3, 0, 1, 0, 0, 0},
        {0, 1, 0, 7, 0, 2},
        {0, 0, 7, 0, 2, 3},
        {0, 0, 0, 2, 0, 4},
        {0, 0, 2, 3, 4, 0}
    };

    cout << "The All-Pairs Shortest Paths distance matrix is:" << endl;
    apsp_with_matrix_multiplication(graph);

    return 0;
}
