import queue
import sys
import time


INF = sys.maxsize


class ContractionHierarchies:
    def __init__(self, n, m, g, g_r, costs, costs_r):
        self.n = n
        self.m = m
        self.g = g
        self.g_r = g_r
        self.costs = costs
        self.costs_r = costs_r
        self.node_level = [0] * n
        self.max_outgoing = [max(w) if len(w) else 1 for w in costs]
        self.min_outgoing = [min(w) if len(w) else INF for w in costs_r]
        self.rank = [INF] * n

    def witness_search(self, s, v, max_dist):
        dist = dict()
        dist[s] = 0

        heap = queue.PriorityQueue()
        heap.put((0, s))
        max_hops = 3
        hops = 0

        while not heap.empty() and hops < max_hops:
            hops += 1
            d, u = heap.get()

            if max_dist <= d:
                break

            for x, w in self.g[u]:
                if self.rank[x] < self.rank[v] or x == v:
                    continue

                if d + w < dist.get(x, INF):
                    dist[x] = d + w
                    heap.put((dist[x], x))

        return dist

    def contract(self, v, adding_shortcuts=False):
        shortcuts = list()
        shortcuts_cover = set()
        shortcut_count = 0
        delta = self.max_outgoing[v] - self.min_outgoing[v]

        for u, u_d in self.g_r[v]:
            if self.rank[u] < self.rank[v]:
                continue

            limit = u_d + delta
            dist = self.witness_search(u, v, limit)

            for w, _ in self.g[v]:
                if self.rank[w] < self.rank[v]:
                    continue

                add_shortcut = True

                for x, d in self.g_r[w]:
                    if self.rank[x] < self.rank[v] or x == v:
                        continue

                    cost = dist.get(x, INF)

                    if self.costs_r[v][u] + self.costs[v][w] >= cost + d:
                        add_shortcut = False
                        break

                if add_shortcut:
                    shortcut_count += 1
                    shortcuts_cover.add(u)
                    shortcuts_cover.add(w)

                    if adding_shortcuts:
                        shortcuts.append((u, w, self.costs_r[v][u] + self.costs[v][w]))

        edge_difference = shortcut_count - len(self.g[v]) - len(self.g_r[v])
        return edge_difference + self.compute_node_level(v) + len(shortcuts_cover), shortcuts

    def compute_node_level(self, v):
        n, level = 0, 0

        for u, _ in self.g[v]:
            if self.rank[u] != INF:
                n += 1
                level = max(self.node_level[u]+1, level)

        for u, _ in self.g_r[v]:
            if self.rank[u] != INF:
                n += 1
                level = max(self.node_level[u]+1, level)

        return n + level/2

    def update_node_level(self, v):
        for u, _ in self.g[v]:
            self.node_level[u] = max(self.node_level[u], self.node_level[v]+1)

        for u, _ in self.g_r[v]:
            self.node_level[u] = max(self.node_level[u], self.node_level[v]+1)

    def add_shortcuts(self, shortcuts):
        for shortcut in shortcuts:
            u, v, w = shortcut
            if self.max_outgoing[u] < w:
                self.max_outgoing[u] = w

            if w < self.min_outgoing[u]:
                self.max_outgoing[v] = w

            self.g[u].append((v, w))
            self.g_r[v].append((u, w))

            self.costs[u][v] = w
            self.costs_r[v][u] = w

    def remove_edges(self):
        for i in range(self.n):
            j, k = 0, len(self.g[i])
            while j < k:
                if self.rank[self.g[i][j][0]] < self.rank[i]:
                    self.costs[i][self.g[i][j][0]] = INF
                    del self.g[i][j]
                    k -= 1
                    continue
                j += 1

            j, k = 0, len(self.g_r[i])
            while j < k:
                if self.rank[self.g_r[i][j][0]] < self.rank[i]:
                    self.costs_r[i][self.g_r[i][j][0]] = INF
                    del self.g_r[i][j]
                    k -= 1
                    continue
                j += 1

    def preprocess(self):
        counter = 0
        rank_count = 0
        pq = queue.PriorityQueue()

        print("n:", self.n)
        for i in range(self.n):
            c, _ = self.contract(i)
            pq.put((c, i))

        while pq.qsize() > 1:
            counter += 1

            _, u = pq.get()
            ved, v = pq.get()

            ed, shortcuts = self.contract(u, adding_shortcuts=True)

            if ed <= ved:
                self.add_shortcuts(shortcuts)
                self.rank[u] = rank_count
                self.update_node_level(u)
            else:
                pq.put((ed, u))

            rank_count += 1
            pq.put((ved, v))

        print("counter:", counter)
        self.remove_edges()

    def query(self, s, t):
        estimate = INF

        pq = queue.PriorityQueue()
        pq_r = queue.PriorityQueue()

        pq.put((0, s))
        pq_r.put((0, t))

        dist = [INF] * self.n
        dist_r = [INF] * self.n
        dist[s] = 0
        dist_r[t] = 0

        visited = [INF] * self.n
        visited_r = [INF] * self.n

        while not pq.empty() or not pq_r.empty():
            if not pq.empty():
                _, u = pq.get()

                if dist[u] <= estimate:
                    for v, w in self.g[u]:
                        if dist[v] > dist[u] + w:
                            dist[v] = dist[u] + w
                            pq.put((dist[v], v))

                visited[u] = True
                if visited_r[u] and dist[u] + dist_r[u] < estimate:
                    estimate = dist[u] + dist_r[u]

            if not pq_r.empty():
                _, u = pq_r.get()

                if dist_r[u] < estimate:
                    for v, w in self.g_r[u]:
                        if dist_r[v] > dist_r[u] + w:
                            dist_r[v] = dist_r[u] + w
                            pq_r.put((dist[v], v))

                visited_r[u] = True
                if visited[u] and dist[u] + dist_r[u] < estimate:
                    estimate = dist[u] + dist_r[u]

        return -1 if estimate == INF else estimate


def readl():
    return map(int, sys.stdin.readline().split())


def init():
    n, m = readl()

    g = [[] for _ in range(n)]
    g_r = [[] for _ in range(n)]

    costs = [[0 for _ in range(n)] for _ in range(n)]
    costs_r = [[INF for _ in range(n)] for _ in range(n)]

    for _ in range(m):
        u, v, w = readl()
        costs[u-1][v-1] = w
        costs_r[v-1][u-1] = w

        g[u-1].append((v-1, w))
        g_r[v-1].append((u-1, w))

    return ContractionHierarchies(n, m, g, g_r, costs, costs_r)


if __name__ == '__main__':
    ch = init()

    start_time = time.time()
    ch.preprocess()
    print("Ready")
    print("preprocessing took %s seconds" % (time.time() - start_time))
    sys.stdout.flush()

    t, = readl()

    for i in range(t):
        s, t = readl()
        start_time = time.time()
        print(ch.query(s-1, t-1))
        print("querying took %s seconds" % (time.time() - start_time))
