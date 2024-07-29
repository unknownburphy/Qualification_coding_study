#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> Edge;

class WeightedGraph {
private:
    vector<int> V;
    vector<Edge> E;
    vector<PII>* neighbor;

public:
    WeightedGraph(const vector<int>& V, const vector<Edge>& E) {
        this->V = V;
        this->E = E;
        neighbor = new vector<PII>[V.size()];

        for (const auto& edge : E) {
            int u = edge.second.first, v = edge.second.second, weight = edge.first;
            neighbor[u].push_back(make_pair(v, weight));
            neighbor[v].push_back(make_pair(u, weight));
        }
    }

    ~WeightedGraph() {
        delete[] neighbor;
    }

    pair<vector<pair<int, int>>, int> prims_mst(int start_vertex) {
        vector<pair<int, int>> mst; // 방문 순서를 보여주기 위함
        set<int> visited; // 방문했는지 여부를 파악하기 위함
        priority_queue<PII, vector<PII>, greater<PII>> min_heap; // 최소 힙

        min_heap.push(make_pair(0, start_vertex));

        int total_weight = 0;

        while (!min_heap.empty()) {
            int weight = min_heap.top().first;
            int current_vertex = min_heap.top().second;
            min_heap.pop();

            if (visited.find(current_vertex) != visited.end()) {
                continue;
            }

            visited.insert(current_vertex);
            mst.push_back(make_pair(current_vertex, weight));
            total_weight += weight;

            for (const auto& neighbor_pair : neighbor[current_vertex]) {
                int neighbor_vertex = neighbor_pair.first;
                int edge_weight = neighbor_pair.second;
                if (visited.find(neighbor_vertex) == visited.end()) {
                    min_heap.push(make_pair(edge_weight, neighbor_vertex));
                }
            }
        }

        return {mst, total_weight};
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] == i) {
            return i;
        } else {
            return find(parent, parent[i]);
        }
    }

    void union_sets(vector<int>& parent, int x, int y) {
        int root_x = find(parent, x);
        int root_y = find(parent, y);
        parent[root_y] = root_x;
    }

    pair<vector<Edge>, int> kruskals_mst() {
        vector<Edge> mst;
        int total_weight = 0;
        sort(E.begin(), E.end());

        vector<int> parent(V.size());
        for (size_t i = 0; i < V.size(); ++i) {
            parent[i] = i;
        }

        for (const auto& edge : E) {
            int u = edge.second.first, v = edge.second.second, weight = edge.first;
            int set_u = find(parent, u);
            int set_v = find(parent, v);

            if (set_u != set_v) {
                mst.push_back(edge);
                total_weight += weight;
                union_sets(parent, set_u, set_v);
            }
        }

        return {mst, total_weight};
    }
};

int main() {
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<Edge> e = {
        {4, {0, 1}}, {8, {0, 7}}, {8, {1, 2}}, {11, {1, 7}}, {7, {7, 8}}, 
        {1, {6, 7}}, {2, {2, 8}}, {6, {6, 8}}, {7, {2, 3}}, {4, {2, 5}}, 
        {2, {5, 6}}, {14, {3, 5}}, {9, {3, 4}}, {10, {4, 5}}
    }; // {weight, {u, v}} 형태

    WeightedGraph graph(v, e);

    auto prim_result = graph.prims_mst(0);
    cout << "Prim's MST:" << endl;
    for (const auto& p : prim_result.first) {
        cout << p.first << " - " << p.second << endl;
    }
    cout << "Total weight: " << prim_result.second << endl;

    auto kruskal_result = graph.kruskals_mst();
    cout << "Kruskal's MST:" << endl;
    for (const auto& t : kruskal_result.first) {
        cout << t.second.first << " - " << t.second.second << " (" << t.first << ")" << endl;
    }
    cout << "Total weight: " << kruskal_result.second << endl;

    return 0;
}
