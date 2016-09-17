package selectionSort

import "testing"

func BenchmarkInsSort(b *testing.B) {
	mockData := []int{}
	for i := 1000; i > 0; i-- {
		mockData = append(mockData, i)
	}

	for i := 0; i < b.N; i++ {
		selection_sort(mockData)
	}
}
