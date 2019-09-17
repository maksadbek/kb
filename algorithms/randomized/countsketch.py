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

p = 2 ** 31 - 1
depth = 4
width = 10

def parent(node):
    if node == 0:
        return 0

    return int((node / 2) - 1)

def child_left(node):
    return node * 2 - 1

def child_right(node):
    return node * 2 + 2

def heapsiftup(heap, node):
    while 0 <= node and heap[node][1] < heap[parent(node)][1]:
        heap[parent(node)], heap[node] = heap[node], heap[parent(node)]
        node = parent(node)

    return node

def heapsiftdown(heap, node):
    n = node

    left = child_left(node)
    while left < len(heap) and heap[left][1] < heap[n][1]:
        n = left

    right  = child_right(node)
    while right < len(heap) and heap[right][1] < heap[n][1]:
        n = right

    if heap[n][0] != heap[node][0]:
        heap[n], heap[node] = heap[node], heap[n]
        heapsiftdown(heap, n)

    return n

def heappush(heap, v):
    """ Add item to the heap.
        >>> heap = []
        >>> heappush(heap, ("Chicago", 1759))
    """
    heap.append(v)
    heapsiftup(heap, len(heap)-1)

def heappop(heap):
    if len(heap) == 0:
        return None

    top = heap[0]

    heap[0] = heap[-1]
    heap.pop()

    if heap:
        heapsiftdown(heap, 0)

    return top

def heapchangepriority(heap, k, p):
    # find it
    for i, v in enumerate(heap):
        if v[0] == k:
            break

    if not v:
        return -1

    old_priority = v[1]
    heap[i] = (k, p)

    if p < old_priority:
        heapsiftup(heap, i)
    else:
        heapsiftdown(heap, i)

def heapfind(heap, k):
    for i in heap:
        if i[0] == k:
            return True

    return False

def heaptop(heap):
    return heap[0]

def genh():
    a, b = random.randint(1, p), random.randint(0, p)

    def h(x):
        return ((a * x + b) % p) % width

    return h

def gent():
    a, b = random.randint(1, p), random.randint(0, p)

    def h(x):
        r = ((a * x + b) % p) % 100
        return -1 if r < 50 else 1

    return h

h = genh()
t = gent()

h = list()
s = list()

for i in range(depth):
    h.append(genh())
    s.append(gent())

c = [[0 for j in range(width)] for i in range(depth)]

sample = [1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 45]

# hash objects in the sample and fill the table
for i in sample:
    for j, r in enumerate(h): 
        c[j][r(i)] += s[j](i)

# count the occurences of items
def approxpoint(i):
    result = []
    for j, r in enumerate(h):
        result.append(c[j][r(i)] * s[j](i))

    return sorted(result)[int(len(result)/2)]

def countsketch(sample, k):
    heap = []

    for i in sample:
        freq = approxpoint(i)
    
        if heapfind(heap, i):
            heapchangepriority(heap, i, freq)
            continue

        if len(heap) < k:
            heappush(heap, (i, freq))
        else:
           fmin, imin = heaptop(heap)
           if fmin < freq:
               heappush(heap, (i, f))
               heappop(heap)

    return heap

trend = countsketch(sample, 3)

print(sample)
while trend:
    print(heappop(trend))
