package main

import "fmt"

func main() {
	const K, N = 4, 8

	dp := [K][N]int{
		[...]int{3, 1, 5, 3, 4, 7, 6, 7},
	}

	for i := 1; i <= K; i++ {
		for j := 0; j+(1<<i) <= N; j++ {
			dp[i][j] = dp[i-1][j] + dp[i-1][j+(1<<(i-1))]
		}
	}

	L, R := 1, 7

	sum := 0

	for i := K; i >= 0; i-- {
		if (1 << i) <= (R - L + 1) {
			sum += dp[i][L]
			L += 1 << i
		}
	}

	println(sum)

}
