package mergeSort

import "testing"

func BenchmarkMergeSort(b *testing.B) {
	mockData := []int{}
	for i := 1000; i > 0; i-- {
		mockData = append(mockData, i)
	}

	for i := 0; i < b.N; i++ {
		mergeSort(mockData, 0, len(mockData)-1)
	}
}
