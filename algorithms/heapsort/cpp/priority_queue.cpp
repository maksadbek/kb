#include "priority_queue.h"
#include "heap.h"
#include "util.h"

int heap_maximum(int A[]) {
	return A[0];
}

int heap_extract_max(int A[], int heap_size) {
	if(heap_size <= 0) {
		return -1;
	}

	int max = A[0];
	A[0] = A[heap_size-1];
	max_heapify(A, 0, heap_size);
	return max;
}

int heap_increase_key(int A[], int i, int key) {
	if (key < A[i] ) {
		return -1;
	}

	A[i] = key;

	while (i > 0 && A[parent(i)] < A[i]) {
		swap(A, i, parent(i));
		i = parent(i);
	}
	return 0;
}

int max_heap_insert(int A[], int key, int heap_size) {
	heap_size += 1;	
	A[heap_size-1] = -9999;
	int result = heap_increase_key(A, heap_size -1, key);
	return result;

}
