#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;


//Breadth first using queue
void BFS(int start, const vector<vector<int>>& graph){
    //keep track of visited
    vector<bool> visited(graph.size(), false);
    //queue for BFS
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()){
        int node = q.front();
        q.pop(); // does not return
        cout << node << "->";

        for (int neighbor : graph[node]){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    cout << endl;   
}

//using recursion (=stack)
void _DFS(int node, const vector<vector<int>>& graph, vector<bool>& visited){
    visited[node] = true;
    cout << node << "->"; // pre-order

    for(int neighbor:graph[node]){
        if(!visited[neighbor]){
            _DFS(neighbor, graph, visited);
        }
    }
    
    //cout << node << " -> "; // post-order
}

void DFS(int start, const vector<vector<int>>& graph){
    //keep track of visited
    vector<bool> visited(graph.size(), false);
    _DFS(start, graph, visited);
    cout << endl;
}

int main(){
    int n = 5;
    vector<vector<int>> graph(n);

    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0};
    graph[3] = {1};
    graph[4] = {1};

    cout << "BFS from 0: ";
    BFS(0, graph);
    
    cout << "DFS from 0: ";
    DFS(0, graph);
    return 0;
}