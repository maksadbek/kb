import math


def parent(n):
    if n == 0:
        return 0

    # TIP: use math.ceil and float
    return math.ceil(float(n) / float(2) - 1)


def right_child(n):
    return n * 2 + 2


def left_child(n):
    return n * 2 + 1


def sift_down(array, i):
    min_index = i

    left = left_child(i)
    if left < len(array) and array[min_index] > array[left]:
        min_index = left

    right = right_child(i)
    if right < len(array) and array[min_index] > array[right]:
        min_index = right

    if min_index != i:
        array[i], array[min_index] = array[min_index], array[i]
        sift_down(array, min_index)


def sift_up(array, i):
    p = parent(i)

    # tip: 0 is a valid value
    if 0 <= p and array[i] < array[p]:
        array[i], array[p] = array[p], array[i]

        sift_up(array, p)


def add(array, v):
    array.append(v)
    sift_up(array, len(array)-1)


def pop(array):
    # TIP: special case
    if len(array) == 1:
        return array.pop()

    top = array[0]

    # TIP: pop()
    array[0] = array.pop()
    sift_down(array, 0)

    return top


array = []

add(array, 9)
add(array, 5)
add(array, 3)
add(array, 2)
add(array, 8)

print(array)

print(pop(array))
print(pop(array))
print(pop(array))
print(pop(array))
print(pop(array))
