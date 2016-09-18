package quicksort

import "fmt"

func Quicksort(A []int, p, r int) {
	if p < r {
		i := Partition(A, p, r)
		fmt.Println(i)
		Quicksort(A, p, i-1)
		Quicksort(A, i+1, r)
	}
}

func Partition(A []int, p, r int) int {
	x := A[r]
	i := p - 1

	for j := p; j < r; j++ {
		if A[j] <= x {
			i += 1
			fmt.Println(A)
			A[i], A[j] = A[j], A[i]
			fmt.Println(A)
			fmt.Println()
		}
	}

	A[i+1], A[r] = A[r], A[i+1]

	return i + 1
}
