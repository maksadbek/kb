import pprint
import heapq
import random

"""
generate t random hash functions h1, h2, ..., ht from items [m] to b = k buckets [1, 2, ..., b]
generate t random hash functions s1, s2, ..., st from items [m] to {-1, +1}

ADD(C, i):
    for r in 1..t:
        C[r, h[r](i) = C[r, h[r](i)] + s[r](i)
    end
end

ESTIMATE(C, i):
    return median[r]{C[r, h[r](i)] * s[r](i)}
end

FINDAPPROXTOP(S):
    for p in S:
        compute frequency f <- APPROXPOINTQUERY(p)
        
        if H contains p:
            update p priority to f
            continue
        end

        if H contains < k elements:
            add p to H with priority of f
        else:
            f', p' <- element in H with smallest key
            if f' < f:
                add p to H with priority of f
                evict f'
            end
        end
end
        
"""

class Heap():
    def __init__(self):
        self.heap = []

    def parent(self, node):
        if node == 0:
            return 0

        return int((node / 2) - 1)

    def child_left(self, node):
        return node * 2 + 1

    def child_right(self, node):
        return node * 2 + 2

    def siftup(self, node):
        while 0 <= node and self.heap[node][1] < self.heap[self.parent(node)][1]:
            self.heap[self.parent(node)], self.heap[node] = self.heap[node], self.heap[self.parent(node)]
            node = self.parent(node)

        return node

    def siftdown(self, node):
        n = node

        left = self.child_left(node)
        if left < len(self.heap) and self.heap[left][1] < self.heap[n][1]:
            n = left

        right = self.child_right(node)
        if right < len(self.heap) and self.heap[right][1] < self.heap[n][1]:
            n = right

        if self.heap[n][1] != self.heap[node][1]:
            self.heap[n], self.heap[node] = self.heap[node], self.heap[n]
            self.siftdown(n)

        return n

    def push(self, v):
        """ Add item to the heap.
            >>> heap = []
            >>> heappush(heap, ("Chicago", 1759))
        """
        self.heap.append(v)
        self.siftup(len(self.heap)-1)

    def pop(self):
        if len(self.heap) == 0:
            return None

        top = self.heap[0]

        self.heap[0] = self.heap[-1]
        self.heap.pop()

        if self.heap:
            self.siftdown(0)

        return top

    def changepriority(self, k, p):
        # find it
        for i, v in enumerate(self.heap):
            if v[0] == k:
                break

        if not v:
            return -1

        old_priority = v[1]
        self.heap[i] = (k, p)

        if p < old_priority:
            self.siftup(i)
        else:
            self.siftdown(i)

    def find(self, k):
        for i in self.heap:
            if i[0] == k:
                return True

        return False

    def top(self):
        if not self.heap:
            return None

        return self.heap[0]

    def size(self):
        return len(self.heap)


class Countsketch():
    def __init__(self, width, depth, sample, k):
        self.width = width
        self.depth = depth
        self.sample = sample
        self.k = k
        self.h = list()
        self.s = list()
        self.c = [[0 for j in range(width)] for i in range(depth)]
        self.p = 2 ** 31 - 1

        for i in range(depth):
            self.h.append(self.genh())
            self.s.append(self.gent())

        # hash objects in the sample and fill the table
        for i in sample:
            for j, r in enumerate(self.h): 
                self.c[j][r(i)] += self.s[j](i)

    def genh(self):
        a, b = random.randint(1, self.p), random.randint(0, self.p)

        def h(x):
            return ((a * x + b) % self.p) % self.width

        return h

    def gent(self):
        a, b = random.randint(1, self.p), random.randint(0, self.p)

        def h(x):
            r = ((a * x + b) % self.p) % 100
            return -1 if r < 50 else 1

        return h

    # count the occurences of items
    def approxpoint(self, i):
        result = []
        for j, r in enumerate(self.h):
            result.append(self.c[j][r(i)] * self.s[j](i))

        return sorted(result)[int(len(result)/2)]

    def topk(self):
        heap = Heap()

        for i in self.sample:
            freq = self.approxpoint(i)
        
            if heap.find(i):
                heap.changepriority(i, freq)
                continue

            if heap.size() < self.k:
                heap.push((i, freq))
            else:
               fmin, imin = heap.top()
               if fmin < freq:
                   heap.push((i, freq))
                   heap.pop()

        trend = []
        while heap.top():
            trend.append(heap.pop())

        trend.reverse()
        return trend

sample=[1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 9, 9, 8, 8, 8, 8, 9]
print(sample)
cs = Countsketch(width=15, depth=5, k=4, sample=sample)
print(cs.topk())
