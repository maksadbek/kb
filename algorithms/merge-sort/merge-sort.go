package mergeSort

import "math"

func merge(A []int, p, q, r int) {
	n1 := q - p + 1 // why +1 ??
	n2 := r - q
	L := make([]int, n1+1)
	R := make([]int, n2+1)

	for i := 0; i < n1; i++ {
		L[i] = A[p+i]
	}

	for i := 0; i < n2; i++ {
		R[i] = A[q+i+1]
	}

	L[n1] = 10000
	R[n2] = 10000

	var i, j int
	for k := p; k <= r; k++ {
		if L[i] <= R[j] {
			A[k] = L[i]
			i = i + 1
		} else {
			A[k] = R[j]
			j = j + 1
		}
	}
}

func mergeSort(A []int, p, r int) {
	if p < r {
		q := int(math.Floor(float64((p + r) / 2)))
		mergeSort(A, p, q)
		mergeSort(A, q+1, r)
		merge(A, p, q, r)
	}
}

/*
func main() {
	A := []int{8, 7, 6, 5, 4, 3, 2, 1}
	mergeSort(A, 0, len(A)-1)
	fmt.Println(A)
}
*/
