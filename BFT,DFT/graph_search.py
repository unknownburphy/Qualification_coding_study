def BFS(graph, start):
    visited = set()
    queue = [start]

    while queue:
        vertex = queue.pop(0)
        if vertex not in visited:
            visited.add(vertex)
            print(vertex, end='->')
            queue.extend(neighbor for neighbor in graph[vertex] if neighbor not in visited)

def _DFS(graph, node, visited):
    visited[node] = True
    print(node, end='->')

    for neighbor in graph[node]:
        if not visited[neighbor]:
            _DFS(graph,neighbor, visited)

def DFS(graph, start):
    visited = [False for _ in range(len(graph))]
    _DFS(graph, start, visited)

if __name__ == "__main__":
    graph = {}
    graph[0] = [1,2]
    graph[1] = [0,3,4]
    graph[2] = [0]
    graph[3] = [1]
    graph[4] = [1]

    print("BFS from 0: ", end = "")
    BFS(graph, 0)
    print("")
    print("DFS from 0: ", end = "")
    DFS(graph,0)