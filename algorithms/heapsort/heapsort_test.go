package heapsort

import (
	"reflect"
	"testing"
)

func TestSort(t *testing.T) {
	want := []int{1, 2, 3, 4, 7, 8, 9, 10, 14, 16}
	heap := NewHeap(4, 1, 3, 2, 16, 9, 10, 14, 8, 7)
	heap.Sort()
	if ok := reflect.DeepEqual(heap.Values, want); !ok {
		t.Errorf("want %v, got %v", want, heap.Values)
	}
}
