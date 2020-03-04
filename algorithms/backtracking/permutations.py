def is_a_solution(a, data):
    return len(a) == data


def process_solution(a, data):
    print(a)


def construct_candidates(a, data):
    return set(range(1, data + 1)) - set(a)


def make_move():
    pass


def unmake_move():
    pass


def backtrack(a, data):
    if is_a_solution(a, data):
        process_solution(a, data)
    else:
        # candidates for next position
        candidate_list = construct_candidates(a, data)
        for candidate in candidate_list:
            make_move()
            backtrack(a + [candidate], data)
            unmake_move()


def generate_permutations(n):
    backtrack([], n)


print(generate_permutations(3))
