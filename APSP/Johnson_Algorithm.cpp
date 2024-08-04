/*
For sparse graphs, running SSSP Dijkstra from every vertex is asymptotically faster 
than repeated squaring or the Floyd-Warshall algorithm.

V * O(VlogV + E) = O(V^2(logV)+VE) (with Fibonacci-heap)
if E = O(V), then the above is O(V^2(logV))

Algorithm: 

1. Let the given graph be G. Add a new vertex s to the graph, add edges from the new vertex to all vertices of G. Let the modified graph be G’. 
2. Run the Bellman-Ford algorithm on G’ with s as the source. Let the distances calculated by Bellman-Ford be h[0], h[1], .. h[V-1]. If we find a negative weight cycle, then return. Note that the negative weight cycle cannot be created by new vertex s as there is no edge to s. All edges are from s. 
3. Reweight the edges of the original graph. For each edge (u, v), assign the new weight as “original weight + h[u] – h[v]”. 
4. Remove the added vertex s and run Dijkstra’s algorithm for every vertex. 
*/

#include <bits/stdc++.h>
using namespace std;

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices
    vector<vector<pair<int, int> > > adj; // Adjacency list

    // Constructor
    Graph(int V)
    {
        this->V = V; // Initialize the number of vertices
        adj.resize(V); // Resize the adjacency list to fit the number of vertices
    }

    // Add edge to the graph
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({ v, w }); // Add an edge from u to v with weight w
    }

    // Implementing Dijkstra Algorithm
    vector<int> dijkstra(int src)
    {
        vector<int> dist(V, INT_MAX); // Initialize distances with infinity
        dist[src] = 0; // Distance to source is 0

        // Min-heap priority queue
        priority_queue<pair<int, int>,
                       vector<pair<int, int> >,
                       greater<pair<int, int> > >
            pq;
        pq.push({ 0, src }); // Push the source vertex

        while (!pq.empty()) {
            int u = pq.top().second; // Get vertex with minimum distance
            pq.pop();

            // Iterate through all adjacent vertices
            for (auto x : adj[u]) {
                int v = x.first;
                int weight = x.second;

                // Relaxation step
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                }
            }
        }

        return dist; // Return the distances
    }

    // Implementing Bellman-Ford Algorithm
    vector<int> bellmanFord(int src)
    {
        vector<int> dist(V, INT_MAX); // Initialize distances with infinity
        dist[src] = 0; // Distance to source is 0

        // Relax all edges V-1 times
        for (int i = 1; i <= V - 1; i++) {
            for (int u = 0; u < V; u++) {
                for (auto x : adj[u]) {
                    int v = x.first;
                    int weight = x.second;

                    if (dist[u] != INT_MAX
                        && dist[u] + weight < dist[v])
                        dist[v] = dist[u] + weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (int u = 0; u < V; u++) {
            for (auto x : adj[u]) {
                int v = x.first;
                int weight = x.second;

                if (dist[u] != INT_MAX
                    && dist[u] + weight < dist[v]) {
                    cout << "Graph contains negative "
                            "weight cycle"
                         << endl;
                    return {};
                }
            }
        }

        return dist; // Return the distances
    }

    // Implementing Johnson Algorithm
    vector<vector<int> > johnsons()
    {
        // Add a new vertex connected by zero-weight edges
        // to all other vertices
        V++;
        adj.resize(V);
        for (int i = 0; i < V - 1; i++)
            adj[V - 1].push_back({ i, 0 });

        // Use Bellman Ford to compute a set of weights for
        // reweighting the edges
        vector<int> h = bellmanFord(V - 1);
        if (h.empty())
            return {};

        // Reweight the edges
        for (int u = 0; u < V; u++) {
            for (auto& x : adj[u]) {
                int v = x.first;
                int& weight = x.second;

                weight = weight + h[u] - h[v];
            }
        }

        // Remove the added vertex and apply Dijkstra from
        // each vertex to all others in the reweighted graph
        V--;
        adj.pop_back();

        vector<vector<int> > distances(V, vector<int>(V));

        for (int s = 0; s < V; s++)
            distances[s] = dijkstra(s);

        // Compute the distances in the original graph by
        // adjusting the distances returned by Dijkstra's
        // algorithm
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (distances[u][v] == INT_MAX)
                    continue;

                distances[u][v] += (h[v] - h[u]);
            }
        }

        return distances; // Return the distance matrix
    }
};

// Driver code
int main()
{
    int V = 4; // Number of vertices
    vector<vector<int> > matrix = { { 0, 0, -2, 0 },
                                    { 4, 0, 3, 0 },
                                    { 0, 0, 0, 2 },
                                    { 0, -1, 0, 0 } };

    // Initialization
    Graph g(V);

    // Add edges to the graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] != 0)
                g.addEdge(i, j, matrix[i][j]);
        }
    }

    // Function Call
    vector<vector<int> > distances = g.johnsons();

    if (distances.empty()) {
        cout << "Negative weight cycle detected." << endl;
        return 0;
    }

    // Print the distance matrix
    // distance[i][j] means shortest path distance from i to j
    cout << "Distance matrix:" << endl;

    cout << "   \t";
    for (int i = 0; i < V; i++)
        cout << setw(3) << i << "\t";

    for (int i = 0; i < V; i++) {
        cout << endl << setw(3) << i << "\t";
        for (int j = 0; j < V; j++) {
            if (distances[i][j] == INT_MAX)
                cout << " X\t";
            else
                cout << setw(3) << distances[i][j] << "\t";
        }
    }

    return 0;
}
