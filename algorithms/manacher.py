def manacher_odd(s):
    print(s)
    p = [0 for _ in range(len(s) + 2)]
    n = len(s)
    s = "$" + s + "^"

    l, r = 1, 1

    for i in range(1, n + 1):
        p[i] = max(0, min(r - i, p[l + r - i]))

        while s[i - p[i]] == s[i + p[i]]:
            # print(i, i - p[i], i + p[i], s[i - p[i]], s[i + p[i]])
            p[i] += 1

        if i + p[i] > r:
            l, r = i - p[i], i + p[i]

    return p[1:-1]


def manacher(s):
    return manacher_odd("#"+"#".join(list(s))+"#")[1:-1]


print(sum([v // 2 if i % 2 == 0 else (v - 1) // 2 for i, v in enumerate(manacher("abababa"))]))
