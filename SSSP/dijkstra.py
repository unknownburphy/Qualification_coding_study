import heapq

# Function to add an edge to the adjacency list
def addEdge(adj, u, v, wt):
    adj[u].append((v, wt))
    adj[v].append((u, wt))

# Function to find the shortest paths from source to all other vertices
def shortestPath(adj, V, src):
    # Create a priority queue to store vertices that are being preprocessed
    pq = []

    # Create an array for distances and initialize all distances as infinite (INF)
    dist = [float('inf')] * V

    # Insert source itself in the priority queue and initialize its distance as 0
    heapq.heappush(pq, (0, src))
    dist[src] = 0

    # Loop until the priority queue becomes empty
    while pq:
        # Extract the vertex with minimum distance from the priority queue
        distance, u = heapq.heappop(pq)

        # Get all adjacent vertices of u
        for v, weight in adj[u]:
            # If there is a shorter path to v through u
            if dist[v] > dist[u] + weight:
                # Update distance of v
                dist[v] = dist[u] + weight
                heapq.heappush(pq, (dist[v], v))

    # Print shortest distances stored in dist[]
    print("Vertex Distance from Source")
    for i in range(V):
        print(i,"   ",dist[i])

# Main function
def main():
    V = 9
    adj = [[] for _ in range(V)]

    # Making the graph
    addEdge(adj, 0, 1, 4)
    addEdge(adj, 0, 7, 8)
    addEdge(adj, 1, 2, 8)
    addEdge(adj, 1, 7, 11)
    addEdge(adj, 2, 3, 7)
    addEdge(adj, 2, 8, 2)
    addEdge(adj, 2, 5, 4)
    addEdge(adj, 3, 4, 9)
    addEdge(adj, 3, 5, 14)
    addEdge(adj, 4, 5, 10)
    addEdge(adj, 5, 6, 2)
    addEdge(adj, 6, 7, 1)
    addEdge(adj, 6, 8, 6)
    addEdge(adj, 7, 8, 7)

    # Finding shortest paths from source vertex 0
    shortestPath(adj, V, 0)

# Call the main function to execute the program
if __name__ == "__main__":
    main()
