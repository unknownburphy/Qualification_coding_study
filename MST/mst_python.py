import heapq

class WeightedGraph():
     
    def __init__(self, V:list, E:list):
        self.V = V[:] # vertex 초기화
        self.E = E[:] # edge 초기화
        self.neighbor = {} # neighbor 초기화
        
        for v in V:
            self.neighbor[v] = []
        
        for (v, w, weight) in E: # undirected graph이므로 두 번 추가
            self.neighbor[v].append([w, weight]) # v -> w
            self.neighbor[w].append([v, weight]) # w -> v   
            
    def prims_mst(self, start_vertex):
        mst = [] # 방문 순서를 보여주기 위함
        visited = set() # 방문했는지 여부를 파악하기 위함
        min_heap = [(0, start_vertex)]

        while min_heap:
            
            weight, current_vertex = heapq.heappop(min_heap) # weight가 가장 작은 vertex가 뽑힘, O(lgV) -> while loop으로 V번 반복하므로 O(VlgV)

            if current_vertex in visited:
                continue

            visited.add(current_vertex)
            mst.append((current_vertex, weight))

            for neighbor, edge_weight in self.neighbor[current_vertex]: # 연결된 edge들의 weight를 모두 heapq에 저장
                if neighbor not in visited:
                    heapq.heappush(min_heap, (edge_weight, neighbor)) # O(lgV) -> for loop으로 최대 E번 반복하므로 O(ElgV)

        total_weight = sum(weight for _, weight in mst)
        
        return mst, total_weight
        # O(VlgV)+O(ElgV) -> O(ElgV)
    
    def find(self, parent, i):
        if parent[i] == i:
            return i
        else:
            return self.find(parent, parent[i])

    def union(self, parent, x, y):
        root_x = self.find(parent, x)
        root_y = self.find(parent, y)
        parent[root_y] = root_x

    def kruskals_mst(self):
        mst = []
        i = 0
        e = 0

        self.E = sorted(self.E, key=lambda item: item[2]) # weight를 기준으로 정렬, O(ElgE)

        parent = {}

        for node in self.V:
            parent[node] = node

        while e < len(self.V) - 1: 
            v, w, weight = self.E[i]
            i = i + 1
            x = self.find(parent, v)
            y = self.find(parent, w)

            if x != y:
                e = e + 1
                mst.append((v, w, weight))
                self.union(parent, x, y)

        total_weight = sum(weight for _, _, weight in mst)

        return mst, total_weight
        # O(ElgE) -> E<V^2이므로 O(ElgV) 

    
v = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
e = [('a', 'b', 5), ('a', 'f', 10), ('a', 'i', 4), ('b', 'c', 3), ('b', 'e', 3), ('c', 'd', 3), ('c', 'e', 3), ('d', 'g', 5), ('d', 'h', 3), ('e', 'g', 2), ('f', 'g', 4)]

weighted_graph = WeightedGraph(v, e)

print("Prim's MST:")
mst, total_weight = weighted_graph.prims_mst('a')
print(mst)
print("Total Weight: ", total_weight)

print("Kruskal's MST:")
mst, total_weight = weighted_graph.kruskals_mst()
print(mst)
print("Total Weight: ", total_weight)
