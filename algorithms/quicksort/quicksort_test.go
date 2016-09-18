package quicksort

import (
	"fmt"
	"testing"
)

func TestQuicksort(t *testing.T) {
	A := []int{2, 8, 7, 1, 3, 5, 6, 4}

	fmt.Println("before: ", A)
	Quicksort(A, 0, len(A)-1)

	fmt.Println("after: ", A)
}
