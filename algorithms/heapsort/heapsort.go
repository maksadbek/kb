package heapsort

import "math"

type Heap struct {
	Values []int
	Length int
}

func NewHeap(n ...int) *Heap {
	h := &Heap{}
	h.Values = make([]int, 0, len(n))
	h.Values = append(h.Values, n...)
	h.Length = len(h.Values) - 1
	h.buildHeap()
	return h
}

func (h *Heap) Left(n int) int {
	return 2*n + 1
}

func (h *Heap) Right(n int) int {
	return 2*n + 2
}

func (h *Heap) Len() int {
	return h.Length
}

func (h *Heap) Swap(a, b int) {
	tmp := h.Values[a]
	h.Values[a] = h.Values[b]
	h.Values[b] = tmp
	return
}

func (h *Heap) Heapify(max int) {
	right := h.Right(max)
	left := h.Left(max)
	largest := max

	if right <= h.Len() && h.Values[largest] < h.Values[right] {
		largest = right
	}

	if left <= h.Len() && h.Values[largest] < h.Values[left] {
		largest = left
	}

	if largest != max {
		h.Swap(largest, max)
		h.Heapify(largest)
	}
	return
}

func (h *Heap) buildHeap() {
	var start int = int(math.Floor(float64(h.Len()) / float64(2)))
	for i := start; i >= 0; i-- {
		h.Heapify(i)
	}
}

func (h *Heap) Sort() {
	start := h.Len()
	for i := start; i >= 1; i-- {
		h.Swap(0, i)
		h.Length -= 1
		h.Heapify(0)
	}
}
