package selectionSort

func selection_sort(L []int) []int {
	for i := 0; i < len(L); i++ {
		min := L[i]
		for j := i; j < len(L); j++ {
			if L[j] < min {
				tmp := min
				min = L[j]
				L[j] = tmp
			}
		}
		L[i] = min
	}
	return L
}
