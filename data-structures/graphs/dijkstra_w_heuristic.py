import queue
import math
import sys


inf = 10 ** 6


def euclidian_dist(u, v):
    return math.sqrt(pow(u[0] - v[0], 2) + pow(u[1] - v[1], 2))


def dijkstra(s, t, n):
    if s == t:
        return 0
    
    dist = [inf for i in range(n)]

    pq = queue.PriorityQueue()
    pq.put((0, 0, s))
    
    dist[s] = 0
    parent = [None for i in range(n)]
    parent[s] = -1;
    discovered = [False for i in range(n)]
    hops = 0
    while not pq.empty():
        heur, w, u = pq.get()
        
        for neighbor in adj[u] or []:
            cost_to_neighbor = w + costs[u][neighbor]
            
            if cost_to_neighbor < dist[neighbor] or not discovered[neighbor]:
                hops += 1
                dist[neighbor] = cost_to_neighbor
                heur = cost_to_neighbor + euclidian_dist(coords[neighbor], coords[t]) - euclidian_dist(coords[u], coords[t])
                pq.put((heur, cost_to_neighbor, neighbor))
                discovered[neighbor] = True
                parent[neighbor] = u

    print("hops: ", hops)
    return dist[t]


def readl():
    return map(int, sys.stdin.readline().split())


if __name__ == '__main__':
    n, m = readl()

    coords = [0 for i in range(n)]
    for i in range(int(n)):
        x, y = readl()
        coords[i] = (x, y)

    costs = [[None for i in range(n)] for i in range(n)]
    adj = [[] for i in range(n)]
    
    for i in range(int(m)):
        u, v, d = readl()
        adj[u-1].append(v-1)
        costs[u-1][v-1] = d

    t, = readl()

    for i in range(t):
        s, t = readl()
        distance = dijkstra(s-1, t-1, n)

        if distance == inf:
            print(-1)
            exit()
        
        print(distance)
