#include <iostream>
#include <vector>
#define MAX_NUM 100000
using namespace std;

class Graph {
    public:
        int V;
        vector<vector<int>> w; // weight가 저장되는 행렬
        vector<vector<int>> pi; // predecessor가 저장되는 행렬
        Graph(int V);
        ~Graph();
        void addDirectedEdge(int u, int v, int weight);
        void FloydWarshall();
        void printAPSP(vector<vector<int>> pi, int i, int j);
};
Graph::Graph(int _V) : V(_V){
    // 행렬 초기화
    for (int i=0; i<V;i++){
        w.push_back(vector<int>(_V, MAX_NUM));
        pi.push_back(vector<int>(_V, MAX_NUM));
        for (int j=0; j<V;j++){
            if (i==j) {
                w[i][j] = 0; // 자기 자긴과의 weight는 0
            }
        }
    }
} 
Graph::~Graph(){}
void Graph::addDirectedEdge(int u, int v, int weight) {
    w[u][v] = weight;
    pi[u][v] = u; // u->v인 경우, predecessor는 u
}
void Graph::FloydWarshall(){
    vector<vector<int>> d = w;
    // 기존의 (i, j) 보다 (i, k) + (k + j) 값이 더 작으면 이 값으로 업데이트 -> 이 과정을 모든 노드 k에 대해 반복
    for (int k=0; k<V; k++){
        for (int i=0; i<V;i++){
            for (int j=0; j<V;j++){
                if (d[i][j] > d[i][k]+d[k][j]){
                    d[i][j] = d[i][k]+d[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
        // // 중간과정 보고 싶으면 print
        // cout << "k: " << k << endl;
        // cout << "weight: " << endl;
        // for (int i=0; i<V;i++){
        //     for (int j=0; j<V;j++){
        //         cout << d[i][j] << "\t";
        //     }
        //     cout << endl;
        // }
        // cout << "pred: " << endl;
        // for (int i=0; i<V;i++){
        //     for (int j=0; j<V;j++){
        //         cout << pi[i][j] << "\t";
        //     }
        //     cout << endl;
        // }
    }

}
void Graph::printAPSP(vector<vector<int>> pi, int i, int j){
    if (i != j){
        if (pi[i][j] == MAX_NUM) {
            cout << "No Path";
        }
        else {
            printAPSP(pi, i, pi[i][j]);
            cout << j << " ";
        }
    }
    else {
        cout << j << " ";
    }
}
int main(){
    int V = 5; 
    Graph g(V);
    g.addDirectedEdge(0, 1, 3);
    g.addDirectedEdge(0, 2, 8);
    g.addDirectedEdge(0, 4, -4);
    g.addDirectedEdge(1, 3, 1);
    g.addDirectedEdge(1, 4, 7);
    g.addDirectedEdge(2, 1, 4);
    g.addDirectedEdge(3, 0, 2);
    g.addDirectedEdge(3, 2, -5);
    g.addDirectedEdge(4, 3, 6);
    
    g.FloydWarshall();
    g.printAPSP(g.pi, 1, 4);    
    // 100000  2       3       4       0
    // 3       100000  3       1       0
    // 3       2       100000  1       0
    // 3       2       3       100000  0
    // 3       2       3       4       100000

    return 0;
}