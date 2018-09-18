package main

import "fmt"

func Rotate(A []int, K int) []int {
	if len(A) == 0 {
		return A
	}
	counter := 0
	bitset := make([]int, len(A))
	setSliceValue(A, bitset, K, 0, A[0], counter)

	return A
}

func setSliceValue(A, bitset []int, N, i, v, counter int) {
	if bitset[i] == 1 {
		if counter != len(A) {
			setSliceValue(A, bitset, N, i+1, A[i+1], counter)
		}
		return
	}
	counter += 1

	bitset[i] = 1

	newIndex := (i + N) % len(A)

	oldVal := A[newIndex]

	A[newIndex] = v

	setSliceValue(A, bitset, N, newIndex, oldVal, counter)
}

func main() {
	a := Rotate([]int{1, 2, 3, 4, 5, 6}, 2)
	expectedSlice := []int{5, 6, 1, 2, 3, 4}

	fmt.Println("expected slice:", expectedSlice)
	fmt.Println("actual slice:", a)
}
