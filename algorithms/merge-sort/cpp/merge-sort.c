#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>

void merge(int* A, int p, int q, int r) {
    int n1 = q - p + 1;     // because there must be at least one object
    int n2 = r - q;

    int* L = (int*)malloc((n1+1)*sizeof(int));
    int* R = (int*)malloc((n2+1)*sizeof(int));

    for(int i=0; i<n1; i++) {
        L[i] = A[p+i];
    }

    for(int i=0; i<n2; i++) {
        R[i] = A[q+i+1];    // the right side must be one value upper
    }
    
    // sentinels, the max number
    L[n1] = 1000;
    R[n2] = 1000;

    int i = 0,j = 0;

    // iterate through p to r
    for(int k = p; k <= r; k++) {
        if(L[i] < R[j]) {
            A[k] = L[i];
            i=i+1;
        } else {
            A[k] = R[j];
            j=j+1;
        }
    }
}

void merge_sort(int* A, int p, int r) {
    if(p < r) {
        int q = floor((p + r)/2);
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

int main() {
    int A[] = {8,7,6,5,4,3,2,1};
    int Alen = sizeof(A)/sizeof(int);
    merge_sort(A, 0, Alen-1);
    for(int i = 0; i < Alen; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
