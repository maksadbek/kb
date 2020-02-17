def coin_change(coins, target):
    if target == 0:
        return 1

    if target < 0:
        return 0
    
    if not coins and target:
        return 0
    
    a = coin_change(coins, target - coins[0])
    b = coin_change(coins[1:], target)

    return a + b

print(coin_change([1, 2, 3], 4))


def min_coin_change(coins, target):
    if target == 0:
        return 0

    if target < 0:
        return 1e10

    if not coins and target:
        return 1e10

    a = min_coin_change(coins, target - coins[0])
    b = min_coin_change(coins[1:], target)

    return min(a+1, b)

print(min_coin_change([1, 2, 3], 4))
