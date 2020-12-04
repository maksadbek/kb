def editdist(t1, t2):
    """
    text1: banana
    text2: nand

    just check every possible variation:

      #1       #2      #3
    banana   banana  anana
     nand   nand     and
    
    Complexity: O(n*m)
    """
    
    if not t1:
        return len(t2)

    if not t2:
        return len(t1)
    
    cost = 1

    if t1[0] == t2[0]:
        cost = 0
    
    min_dist = min(
        editdist(t1[1:], t2) + 1,
        editdist(t1, t2[1:]) + 1,
        editdist(t1[1:], t2[1:]) + cost,
    )

    return min_dist

print(editdist("banana", "nand"))  # 3
