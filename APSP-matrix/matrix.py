import numpy as np

def apsp_with_matrix_multiplication(graph):
    # Number of vertices in the graph
    n = len(graph)
    
    # Initialize distance matrix with graph values
    dist = np.array(graph, dtype=float)
    
    # Replace all zeros with infinity where i != j
    np.fill_diagonal(dist, 0)
    dist[dist == 0] = np.inf
    np.fill_diagonal(dist, 0)
    
    # Iterate log(n) times
    for _ in range(int(np.ceil(np.log2(n)))):
        dist = np.minimum(dist, dist @ dist)
    
    return dist

# Example usage
graph = [
    [0, 3, 0, 0, 0, 0],
    [3, 0, 1, 0, 0, 0],
    [0, 1, 0, 7, 0, 2],
    [0, 0, 7, 0, 2, 3],
    [0, 0, 0, 2, 0, 4],
    [0, 0, 2, 3, 4, 0]
]

distance_matrix = apsp_with_matrix_multiplication(graph)
print("The All-Pairs Shortest Paths distance matrix is:")
print(distance_matrix)
