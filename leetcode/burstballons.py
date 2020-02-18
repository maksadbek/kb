def burst_naive(nums):
    def index(nums, i):
        if 0 <= i < len(nums):
            return nums[i]

        return 1

    n = len(nums)
    if n == 0:
        return 0

    if n == 1:
        return nums[0]

    if n == 2:
        return nums[0] * nums[1] + max(nums[0], nums[1])

    res = [index(nums, i-1) * index(nums, i) * index(nums, i+1) + burst_naive(nums[:i] + nums[i+1:]) for i in range(n)]

    return max(res)


print(burst_naive([3, 1, 5, 8]))


def burst_faster(balloons, left, right, tabs):
    print("   \n\n " * tabs, left, right)

    score = 0
    for i in range(left, right+1):
        a = balloons[left-1] * balloons[i] * balloons[right+1]
        a += burst_faster(balloons, left, i - 1, tabs+1)
        a += burst_faster(balloons, i + 1, right, tabs+1)

        score = max(score, a)

    return score


array = [3, 1, 5, 8]
array = [1] + array + [1]

print(burst_faster(array, 1, len(array)-2, 0))

# def burst(self, balloons):
#     balloons = [1] + balloons + [1]
#     memo = {}
#
#     def dp(left, right):
#         if left + 1 == right:
#             return 0
#
#         if (left, right) in memo:
#             return memo[(l, r)]
#
#             memo[(left, right)] = max(dp(left, i) + nums[left] * nums[i] * nums[right] + dp(i, right) for i in range(l + 1, r))
#
#     return dp(0, len(nums) - 1)
