from collections import namedtuple
from pprint import pprint

Item = namedtuple("Item", ["value", "weight"])

def knapsack(items, w):
    data = [[0 for i in range(w+1)] for j in range(len(items)+1)]

    for i in range(1, len(items)+1):
        v = items[i-1]

        for j in range(v.weight, w+1):
            data[i][j] = max(data[i-1][j], data[i-1][j - v.weight] + v.value)

    return data[len(items)][w]


def knapsack2(items, w):
    data = [0 for i in range(w+1)]

    for i in range(1, len(items)+1):
        v = items[i-1]

        for j in range(w, v.weight-1, -1):
            data[j] = max(data[j], data[j-v.weight] + v.value)
            pprint(data)

    return data[w]

items = [Item(1, 2), Item(2, 3), Item(3,4), Item(4,5)]
pprint(items)
print(knapsack(items, 10))
print(knapsack2(items, 10))
