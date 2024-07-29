#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX

#define MAX_VERTICES 100
#define MAX_EDGES 200

typedef struct {
    int weight;
    int start;
    int end;
} Edge;

typedef struct {
    int vertex;
    int weight;
} Node;

typedef struct {
    Node* heap[MAX_EDGES];
    int size;
} MinHeap;

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->heap[left]->weight < minHeap->heap[smallest]->weight) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->heap[right]->weight < minHeap->heap[smallest]->weight) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&minHeap->heap[smallest], &minHeap->heap[idx]);
        minHeapify(minHeap, smallest);
    }
}

Node* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        return NULL;
    }

    Node* root = minHeap->heap[0];
    minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->heap[i] = node;

    while (i && minHeap->heap[i]->weight < minHeap->heap[(i - 1) / 2]->weight) {
        swap(&minHeap->heap[i], &minHeap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

void primsMST(int vertices, Edge edges[], int numEdges, int startVertex) {
    int inMST[MAX_VERTICES] = {0}; // 방문했는지 여부를 기록
    int parent[MAX_VERTICES]; // 나중에 print할 때 사용하기 위함
    int key[MAX_VERTICES]; // weight 저장 용도

    for (int i = 0; i < vertices; ++i) {
        key[i] = INT_MAX; // 처음에는 모든 weight를 무한대로 만들어줌
        parent[i] = -1;
    }

    MinHeap* minHeap = createMinHeap();
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->vertex = startVertex;
    startNode->weight = 0;
    insertMinHeap(minHeap, startNode); // mean heap에 첫번째 노드를 push
    key[startVertex] = 0; // weight는 0으로 저장

    while (minHeap->size > 0) {
        Node* minNode = extractMin(minHeap); // mean heap에서 pop
        int u = minNode->vertex;
        free(minNode);
        inMST[u] = 1; // 방문했다고 표시

        for (int i = 0; i < numEdges; ++i) {
            int v = edges[i].end;
            int weight = edges[i].weight;

            if (edges[i].start == u && !inMST[v] && key[v] > weight) {
                key[v] = weight;
                parent[v] = u;
                Node* node = (Node*)malloc(sizeof(Node));
                node->vertex = v;
                node->weight = key[v];
                insertMinHeap(minHeap, node); // 이웃노드를 push
            }
        }
    }

    printf("Prim's MST:\n");
    for (int i = 1; i < vertices; ++i) {
        if (parent[i] != -1) {
            printf("%d - %d\n", parent[i], i);
        }
    }
}

int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootY] = rootX;
}

void heapify(Edge arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight) {
        largest = left;
    }

    if (right < n && arr[right].weight > arr[largest].weight) {
        largest = right;
    }

    if (largest != i) {
        Edge temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(Edge arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        Edge temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void kruskalsMST(int vertices, Edge edges[], int numEdges) {
    heapSort(edges, numEdges);

    int parent[MAX_VERTICES];
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
    }

    Edge mst[MAX_EDGES];
    int mstSize = 0;
    int totalWeight = 0;

    for (int i = 0; i < numEdges; ++i) {
        int u = edges[i].start;
        int v = edges[i].end;
        int weight = edges[i].weight;

        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            mst[mstSize++] = edges[i];
            totalWeight += weight;
            unionSets(parent, setU, setV);
        }
    }

    printf("Kruskal's MST:\n");
    for (int i = 0; i < mstSize; ++i) {
        printf("%d - %d (%d)\n", mst[i].start, mst[i].end, mst[i].weight);
    }
    printf("Total weight: %d\n", totalWeight);
}

int main() {
    int vertices = 9;
    Edge edges[] = {
        {4, 0, 1}, {8, 0, 7}, {8, 1, 2}, {11, 1, 7}, {7, 7, 8}, 
        {1, 6, 7}, {2, 2, 8}, {6, 6, 8}, {7, 2, 3}, {4, 2, 5}, 
        {2, 5, 6}, {14, 3, 5}, {9, 3, 4}, {10, 4, 5}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    primsMST(vertices, edges, numEdges, 0); // 시작할 노드를 임의로 0으로 지정
    kruskalsMST(vertices, edges, numEdges);

    return 0;
}
