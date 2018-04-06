#include <stdlib.h>
#include <stdio.h>

int partition(int* A,int lo, int hi);

void quicksort(int* A, int lo, int hi) {
	if(lo < hi) {
		int p = partition(A, lo, hi);
		quicksort(A, lo, p - 1);
		quicksort(A, p + 1, hi);
	}
}

int partition(int* A, int lo, int hi) {
	int pivot = A[hi];
	int i = lo - 1;
	for(int j = lo; j < hi - 1; j++) {
		if(A[j] < pivot) {
			i = i + 1;
			int tmp = A[i];;
			A[i] = A[j];
			A[j] = tmp;
		}

		int t = A[i+1];
		A[i+1] = hi;
		A[hi] = t;
	}

	return i + 1;
}

int main(int argc, char** argv) {
	int a[] = {1,2,3,3,5,5};
	quicksort(a, 0, (sizeof(a) / sizeof(int)) - 1);

	for(int i = 0; i < sizeof(a) / sizeof(int); i++) {
		printf("%d, ", a[i]);
	}

	return 0;
}
