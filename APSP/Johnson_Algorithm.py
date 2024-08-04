import heapq  # 힙 큐 모듈을 임포트하여 우선순위 큐로 사용

class Graph:
    # Neighbour 클래스: 인접한 이웃 정점을 나타내는 클래스
    class Neighbour:
        def __init__(self, destination, weight):
            self.destination = destination  # 목적지 정점
            self.weight = weight  # 엣지 가중치

    # Graph 클래스 초기화
    def __init__(self, vertices, adjacency_matrix):
        self.vertices = vertices  # 정점의 수
        self.adjacency_list = [[] for _ in range(vertices)]  # 인접 리스트 초기화

        # 인접 행렬을 기반으로 인접 리스트 생성
        for i in range(vertices):
            for j in range(vertices):
                if adjacency_matrix[i][j] != 0:
                    self.add_edge(i, j, adjacency_matrix[i][j])

    # 엣지 추가 메서드
    def add_edge(self, source, destination, weight):
        self.adjacency_list[source].append(self.Neighbour(destination, weight))  # 인접 리스트에 엣지 추가

    # Dijkstra 알고리즘
    def dijkstra(self, source):
        is_visited = [False] * self.vertices  # 방문 여부 리스트
        distance = [float('inf')] * self.vertices  # 최단 거리 리스트 초기화
        distance[source] = 0  # 출발점의 거리는 0으로 설정

        heap = [(0, source)]  # 우선순위 큐 초기화

        while heap:
            dist, node = heapq.heappop(heap)  # 최단 거리가 가장 짧은 정점을 꺼냄
            if is_visited[node]:
                continue
            is_visited[node] = True  # 현재 정점을 방문으로 표시

            # 현재 정점의 모든 인접 정점 확인
            for neighbour in self.adjacency_list[node]:
                if (not is_visited[neighbour.destination] and
                        dist + neighbour.weight < distance[neighbour.destination]):
                    # 새로운 최단 경로를 발견하면 거리 업데이트
                    distance[neighbour.destination] = dist + neighbour.weight
                    heapq.heappush(heap, (distance[neighbour.destination], neighbour.destination))  # 우선순위 큐에 추가

        return distance  # 최종 최단 거리 리스트 반환

    # Bellman-Ford 알고리즘
    def bellmanford(self, source):
        distance = [float('inf')] * self.vertices  # 최단 거리 리스트 초기화
        distance[source] = 0  # 출발점의 거리는 0으로 설정

        # 모든 엣지를 V-1번 반복하여 최단 거리 계산
        for _ in range(self.vertices - 1):
            for current_vertex in range(self.vertices):
                for neighbour in self.adjacency_list[current_vertex]:
                    if (distance[current_vertex] != float('inf') and
                            distance[current_vertex] + neighbour.weight < distance[neighbour.destination]):
                        # 새로운 최단 경로를 발견하면 거리 업데이트
                        distance[neighbour.destination] = distance[current_vertex] + neighbour.weight

        # 음수 사이클 검출
        for current_vertex in range(self.vertices):
            for neighbour in self.adjacency_list[current_vertex]:
                if (distance[current_vertex] != float('inf') and
                        distance[current_vertex] + neighbour.weight < distance[neighbour.destination]):
                    return None  # 음수 사이클이 발견되면 None 반환

        return distance  # 최종 최단 거리 리스트 반환

    # Johnson's 알고리즘
    def johnsons(self):
        self.vertices += 1  # 가상의 정점을 추가
        # 가상의 정점에서 모든 정점으로 가중치 0인 엣지 추가
        self.adjacency_list.append([self.Neighbour(i, 0) for i in range(self.vertices - 1)])

        h = self.bellmanford(self.vertices - 1)  # 가상의 정점을 이용해 Bellman-Ford 알고리즘 수행
        if h is None:
            return None  # 음수 사이클이 발견되면 None 반환

        # 엣지 가중치 재설정
        for u in range(self.vertices):
            for neighbour in self.adjacency_list[u]:
                v, w = neighbour.destination, neighbour.weight
                neighbour.weight = w + h[u] - h[v]

        self.adjacency_list.pop()  # 가상의 정점을 제거
        self.vertices -= 1

        distances = []
        # 각 정점에 대해 Dijkstra 알고리즘을 수행하여 최단 거리 계산
        for s in range(self.vertices):
            distances.append(self.dijkstra(s))

        # 거리 값을 원래 가중치로 보정
        for u in range(self.vertices):
            for v in range(self.vertices):
                if distances[u][v] != float('inf'):
                    distances[u][v] += h[v] - h[u]

        return distances  # 최종 모든 쌍 최단 거리 행렬 반환

# Driver Code
if __name__ == "__main__":
    vertices = 4
    matrix = [[0, 0, -2, 0],
              [4, 0, 3, 0],
              [0, 0, 0, 2],
              [0, -1, 0, 0]]

    # 그래프 초기화
    graph = Graph(vertices, matrix)

    # Johnson's 알고리즘 호출
    distances = graph.johnsons()

    if distances is None:
        print("Negative weight cycle detected.")
    else:
        # 거리 행렬 출력
        # distances[i][j]는 i에서 j로 가는 최단 거리를 나타냄
        print("Distance matrix:")
        print("\t", end="")
        for i in range(vertices):
            print(f"{i}\t", end="")
        print()
        for i in range(vertices):
            print(f"{i}\t", end="")
            for j in range(vertices):
                if distances[i][j] == float('inf'):
                    print(" X\t", end="")
                else:
                    print(f"{distances[i][j]}\t", end="")
            print()
