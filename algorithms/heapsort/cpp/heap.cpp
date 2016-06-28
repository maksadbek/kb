#include <cmath>
#include "heap.h"
#include "util.h"
#include <iostream>

int parent(int i) {
	return ceil(i/2);
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void max_heapify(int A[], int i, int heap_size) {
	int l = left(i);
	int r = right(i);
	int largest = i;

	if ( l <= heap_size && A[l] > A[largest]) {
		largest = l;
	}

	if ( r <= heap_size && A[r] > A[largest]) {
		largest = r;
	}

	if ( largest != i ) {
		swap(A, i, largest);
		max_heapify(A, largest, heap_size);
	}
	return;
}

void build_max_heap(int A[], int heap_size) {
	for ( int i = ceil(heap_size / 2); i >= 0; i-- ) {
		max_heapify(A, i, heap_size);
	}
	return;
}

void heapsort(int A[], int length) {
	build_max_heap(A, length);

	for ( int i = length; i >= 1; i--) {
		swap(A, 0, i);
		length = length - 1;
		max_heapify(A, 0, length);
	}
	return;
}
