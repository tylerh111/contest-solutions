
class Graph():
    def __init__(self, vertices):
        # graph[u][v]
        #  := 0 if no edge from u to v
        #  := 1 if edge from u to v
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]
        self.graph_t = [[0 for _ in range(vertices)] for _ in range(vertices)]
        self.V = vertices

    def addEdge(self, u, v):
        self.graph[u][v] = 1
        self.graph_t[v][u] = 1
        
        
    def isCyclicUtil(self, v, visited, extending):
        visited[v] = True
        extending[v] = True
        
        for neighbor in self.graph[v]:
            if not visited[neighbor]:
                if self.isCyclicUtil(neighbor, visited, extending):
                    return True
                elif extending[neighbor]:
                    return True
        
        extending[v] = False
        return False
    
    def isCyclic(self):
        visited = [False] * self.V
        extending = [False] * self.V
        
        for node in self.graph:
            if not visited[node]:
                if self.isCyclicUtil(node, visited, extending):
                    return True
        
        return False
    
    def getVertexInNeighbors(self, v):
        return [i for i, x in enumerate(self.graph[v]) if x == 1]
    
    def getVertexOutNeighbors(self, v):
        return [i for i, x in enumerate(self.graph) if x[v] == 1]
    
    def getVertexNeighbors(self, v):
        return (self.getVertexInIncidents(v),
               self.getVertexOutIncidents(v))
        
    
    def getDepthUtil(self, table, depth, level):
        for v in level:
            table[v] = depth
        
        nextLevel = set()
        
        for u in level:
            for v in self.getVertexOutNeighbors(u):
                is_visitable = True
                
                if v not in nextLevel:                
                    for x in self.getVertexInNeighbors(v):
                        if table[x] == 0:
                            is_visitable = False
                            break
                
                    if is_visitable:
                        nextLevel.add(v)
        
        if nextLevel:
            self.getDepthUtil(table, depth+1, nextLevel)
        
    
    def getDepth(self):
        first_level = set()
        
        for v in range(self.V):
            if len(self.getVertexInNeighbors(v)) == 0:
                first_level.add(v)
        
        table = [0 for _ in range(self.V)]
        self.getDepthUtil(table, 1, first_level)
        
        if 0 in table:
            return None
        
        return max(table)
        
    
                      
# get input
vertices = dict()
n_vert = int(input())

for i in range(n_vert):
    v = input().rstrip()
    vertices[v] = i

n_edge = int(input())

g = Graph(n_vert)

for i in range(n_edge):
    edge = input().rstrip()
    v1, v2 = edge.split(' ')
    g.addEdge(vertices[v1], vertices[v2])


output = g.getDepth()

if output is None:
    print('never')
else:
    print(output)




