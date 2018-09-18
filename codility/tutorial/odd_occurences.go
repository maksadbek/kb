package main

import (
	"sort"
)

func Solution(A []int) int {
	if len(A) == 1 {
		return A[0]
	}

	sort.Ints(A)

	for i := 1; i <= len(A); i += 2 {
		// if it is last elem
		// then return it
		if i == len(A) {
			return A[i-1]
		}

		if A[i-1] != A[i] {
			return A[i-1]
		}
	}

	return 0
}

func main() {
	println("solution:", Solution([]int{2, 2, 3, 3, 4}))
}
