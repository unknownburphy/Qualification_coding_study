#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000  // 최대 정점 수 정의
#define MAX_EDGES 1000  // 최대 간선 수 정의
#define INF INT_MAX  // 무한대 값 정의 // 혹시 gradescope를 쓸 때 잘 안된다면, 이걸 2147483647로 바꿔야 할 수도 있습니다.

// Edge 구조체 정의
typedef struct {
    int source;  // 출발 정점
    int destination;  // 도착 정점
    int weight;  // 간선 가중치
} Edge;

// Bellman-Ford 함수 정의
void bellmanFord(Edge edges[], int vertices, int edgeCount, int source) {
    int distance[MAX_VERTICES];  // 각 정점까지의 최단 거리 배열

    // 모든 정점의 거리를 무한대로 초기화
    for (int i = 0; i < vertices; ++i)
        distance[i] = INF;
    // 출발 정점의 거리를 0으로 설정
    distance[source] = 0;

    // 간선을 V-1번 이완 (relaxation)
    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edgeCount; ++j) {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;
            // 새로운 경로가 더 짧은 경우 거리 갱신
            if (distance[u] != INF && distance[u] + weight < distance[v])
                distance[v] = distance[u] + weight;
        }
    }

    // 음수 가중치 사이클 확인
    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].source;
        int v = edges[i].destination;
        int weight = edges[i].weight;
        // 음수 사이클이 존재하는 경우
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            printf("Negative cycle detected\n");
            return;
        }
    }

    // 결과 출력
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i)
        printf("%d \t\t %d\n", i, distance[i]);
}

// 메인 함수
int main() {
    int vertices = 6;  // 정점의 개수
    int edgeCount = 8;  // 간선의 개수

    // 간선 배열 정의
    Edge edges[MAX_EDGES] = {
        {0, 1, 5}, {0, 2, 7}, {1, 2, 3},
        {1, 3, 4}, {1, 4, 6}, {3, 4, -1},
        {3, 5, 2}, {4, 5, -3}
    };

    // 출발 정점을 0으로 하여 Bellman-Ford 함수 호출
    bellmanFord(edges, vertices, edgeCount, 0);

    return 0;
}
