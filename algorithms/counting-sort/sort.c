#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
* counting sort
*/
void
sort(int A[], int B[], int k, int length) {
	int C[k];
	for(int i = 0; i < k; i++) {
		C[i] = 0;
	}

	for(int i = 0; i < length; i++) {
		C[A[i]] = C[A[i]] + 1;
	}

	for(int i = 1; i <= k; i++) {
		C[i] = C[i] + C[i-1];
	}

	for(int i = length-1; i >= 0; i--) {
		int index = C[A[i]];
		int val = A[i];

		/*
		* need to decrement the index
		* because it is always greater than 0.
		*/
		B[index-1] = val;

		C[A[i]] = C[A[i]] - 1;
	}

	return;
}

int
main(int argc, char** argv) {
	int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
	int B[5];

	sort(A, B, 6, 8);
	
	printf("sorted numbers: ");
	for(int i = 0; i < 8; i++) {
		printf("%d ", B[i]);
	}
	printf("\n");
	
	return 0;
}
