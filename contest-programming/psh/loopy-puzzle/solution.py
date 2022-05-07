
# construct grid
r, c = [int(x) for x in input().split(' ')]

grid = [None for _ in range(r*c)]
countx = [None for _ in range(r*c)]

def getAdjacent(i, r, c):
    adj = []
    if i >= c        and grid[i-c] is not None: adj.append(grid[i-c]) # above
    if i < (c*(r-1)) and grid[i+c] is not None: adj.append(grid[i+c]) # below
    if i % c != 0    and grid[i-1] is not None: adj.append(grid[i-1]) # left
    if i % c != c-1  and grid[i+1] is not None: adj.append(grid[i+1]) # right
    return adj

def getGraphPos(x):
    if grid[x] is None:
        return None
    
    return x - countx[x]

def getGridPos(x):
    return x + countx[x]



class Graph():
    def __init__(self, vertices):
        # graph[u][v]
        #  := 0 if no edge from u to v
        #  := 1 if edge from u to v
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]
        self.o_list = [abs(x) for x in grid if x is not None and x < 0]
        self.V = vertices
    
    def addEdge(self, u, v, val=1):
        self.graph[u][v] = 1
        self.graph[v][u] = 1
    
    def print(self):
        print(''.rjust(len(str(self.V))+1), end=' ')
        for i in range(self.V):
            print(str(i).rjust(len(str(self.V))), end=' ')
        print()
            
        for i, row in enumerate(self.graph):
            print(str(i).ljust(len(str(self.V))), end=' ')
            print('[' + ''.ljust(i*(len(str(self.V))+1)), end='')
            for j, col in enumerate(self.graph[i]):
                if j >= i:
                    print(str(col).rjust(len(str(self.V))), end=' ')
            print(']')
            
            
    ''' Check if this vertex is an adjacent vertex
        of the previously added vertex and is not
        included in the path earlier '''
    def isSafe(self, v, pos, path):
        # Check if current vertex and last vertex
        # in path are adjacent
        if self.graph[ path[pos-1] ][v] == 0:
            return -1
        
        # Check if current vertex not already in path
        for vertex in path:
            if vertex == v:
                return -1
            
        # Check if current vertex is an O (i.e. is 2 in graph)
        if v in self.o_list:
            
            opntPathPos = getGridPos(path[pos-1])
            opntV = getGridPos(v)
            
            # check if there exists a right if coming from left
            if opntPathPos == opntV-1 and opntV+1 < r*c:
                x = getGraphPos(opntV+1)
                if x is not None and self.graph[v][x] != 0:
                    return x
            
            # check if there exists a left if coming from right
            if opntPathPos == opntV+1 and 0 <= opntV-1:
                x = getGraphPos(opntV-1)
                if x is not None and self.graph[v][x] != 0:
                    return x
            
            # check if there exists a down if coming from up
            if opntPathPos != opntV-1 and opntPathPos < opntV and opntV+c < r*c:
                x = getGraphPos(opntV+c)
                if x is not None and self.graph[v][x] != 0:
                    return x
            
            # check if there exists an up if cominf grom down
            if opntPathPos != opntV+1 and opntPathPos > opntV and 0 <= opntV+c:
                x = getGraphPos(opntV-c)
                if x is not None and self.graph[v][x] != 0:
                    return x
            
            return -1
        
        return v
    
    
    def expandToVertex(self, path, pos, v):
        x = self.isSafe(v, pos, path)
        if x != -1:
            path[pos] = v
            
            if x != v:
                if self.hamCycleUtil(path, pos+1, x):
                    return True
            else:
                if self.hamCycleUtil(path, pos+1):
                    return True

            # Remove current vertex if it doesn't
            # lead to a solution 
            path[pos] = -1
            
        return False
    
    
    def hamCycleUtil(self, path, pos, x=None):
        
        # base case: if path is complete, check endpoints are conntected
        if pos == self.V:
            return self.graph[ path[pos-1] ][ path[0] ] == 1
        
        # if x is required to expand, expand it
        if x is not None:
            if self.expandToVertex(path, pos, x):
                return True
        # otherwise loop over all vertices
        else:
            for v in range(1, self.V):
                if self.expandToVertex(path, pos, v):
                    return True
            
        return False
    
    def hamCycle(self):
        path = [-1] * self.V
        
        # starting at vertex 0
        path[0] = 0
        
        self.hamCycleUtil(path, 1)
        return path
    
    
    

def getGridCenterSquare(s, r, c):
    return (3*(s//c)+1, 3*(s%c)+1)


# t := type ('X', '.')
# direction:
#   0 := up, down
#   1 := left, right
#   2 := up, left
#   3 := up, right
#   4 := down, left
#   5 := down, right
def fillGridSquare(out, i, j, t, direction=None):
    if t == 'X':
        out[i-1][j-1] = out[i][j-1] =  out[i+1][j-1] = 'X'
        out[i-1][j]   = out[i][j]   =  out[i+1][j]   = 'X'
        out[i-1][j+1] = out[i][j+1] =  out[i+1][j+1] = 'X'
    elif t == '.':
        out[i-1][j-1] = out[i][j-1] =  out[i+1][j-1] = '.'
        out[i-1][j]   = out[i][j]   =  out[i+1][j]   = '.'
        out[i-1][j+1] = out[i][j+1] =  out[i+1][j+1] = '.'
    elif t == '+':
        out[i-1][j-1] =  out[i+1][j-1] = '.'
        out[i-1][j+1] =  out[i+1][j+1] = '.'
        out[i][j] = '+'
        out[i-1][j] = '|' if direction == 0 or direction == 2 or direction == 3 else '.'
        out[i][j-1] = '-' if direction == 1 or direction == 2 or direction == 4 else '.'
        out[i][j+1] = '-' if direction == 1 or direction == 3 or direction == 5 else '.'
        out[i+1][j] = '|' if direction == 0 or direction == 4 or direction == 5 else '.'
            




vertices = 0
cntx = 0
for i in range(r):
    rows= list(input())
    for j, x in enumerate(rows):
        if x == '.':
            grid[i*c + j] = vertices
            countx[vertices] = cntx
            vertices += 1
        elif x == 'O':
            # 0 is always appears in a corner
            # thus 'O' cannot be the frist vertex
            # hence we can use negatives
            grid[i*c + j] = -vertices
            countx[vertices] = cntx
            vertices += 1
        else:
            cntx += 1
            grid[i*c + j] = None
            countx[i*c + j] = -cntx

            
g = Graph(vertices)

for x, u in enumerate(grid):
    if u is not None:
        adj = getAdjacent(x, r, c)
        for v in adj:
            if u < 0 or v < 0:
                g.addEdge(abs(u), abs(v), 2)
            else:
                g.addEdge(u, v)
            
path = g.hamCycle()
out = [[None for _ in range(3*c)] for _ in range(3*r)]

for s, x in enumerate(grid):
    (i,j) = getGridCenterSquare(s, r, c)
    if x is None:
        fillGridSquare(out, i, j, 'X')
    else:
        fillGridSquare(out, i, j, '.')
        

for s in range(-1, vertices-1):
    u = path[s-1]
    x = path[s]
    v = path[s+1]
    pos = getGridPos(x)
    (i,j) = getGridCenterSquare(pos, r, c)
    
    # left, right
    if u-1 == x and v+1 == x or v-1 == x and u+1 == x:
        fillGridSquare(out, i, j, '+', 1)
    # left, up
    elif u+1 == x and v < x or v+1 == x and u < x:
        fillGridSquare(out, i, j, '+', 2)
    # left, down
    elif u+1 == x and x < v or v+1 == x and x < u:
        fillGridSquare(out, i, j, '+', 4)
    # right, up
    elif u-1 == x and v < x or v-1 == x and u < x:
        fillGridSquare(out, i, j, '+', 3)
    # right, down
    elif u-1 == x and x < v or v-1 == x and x < u:
        fillGridSquare(out, i, j, '+', 5)
    # up, down
    elif u < x and x < v or v < x and x < u:
        fillGridSquare(out, i, j, '+', 0)
        

for row in out:
    for col in row:
        print(col, end='')
    print()



