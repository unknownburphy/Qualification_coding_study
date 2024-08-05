MAX_NUM = 100000

class Graph:
    def __init__(self, V):
        self.V = V
        self.w = [[MAX_NUM] * V for _ in range(V)]
        self.pi = [[MAX_NUM] * V for _ in range(V)]
        for i in range(V):
            self.w[i][i] = 0

    def addDirectedEdge(self, u, v, weight):
        self.w[u][v] = weight
        self.pi[u][v] = u

    def FloydWarshall(self):
        d = [row[:] for row in self.w]
        for k in range(self.V):
            for i in range(self.V):
                for j in range(self.V):
                    if d[i][j] > d[i][k] + d[k][j]:
                        d[i][j] = d[i][k] + d[k][j]
                        self.pi[i][j] = self.pi[k][j]

    def printAPSP(self, pi, i, j):
        if i != j:
            if pi[i][j] == MAX_NUM:
                print("No Path", end=" ")
            else:
                self.printAPSP(pi, i, pi[i][j])
                print(j, end=" ")
        else:
            print(j, end=" ")

V = 5
g = Graph(V)
g.addDirectedEdge(0, 1, 3)
g.addDirectedEdge(0, 2, 8)
g.addDirectedEdge(0, 4, -4)
g.addDirectedEdge(1, 3, 1)
g.addDirectedEdge(1, 4, 7)
g.addDirectedEdge(2, 1, 4)
g.addDirectedEdge(3, 0, 2)
g.addDirectedEdge(3, 2, -5)
g.addDirectedEdge(4, 3, 6)

g.FloydWarshall()
g.printAPSP(g.pi, 1, 4)