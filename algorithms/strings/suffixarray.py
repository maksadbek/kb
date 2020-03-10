from collections import defaultdict


def bucket_sort(s, bucket, order):
    d = defaultdict(list)

    for i in bucket:
        k = s[i:i+order]
        d[k].append(i)

    result = []

    for k, v in sorted(d.items()):
        if 1 < len(v):
            result += bucket_sort(s, v, order * 2)
        else:
            result.append(v[0])

    return result


def make_suffix_array(words):
    """
        Manbery Myers method of making a suffix array
    """

    return bucket_sort(words, (i for i in range(len(words))), 1)
