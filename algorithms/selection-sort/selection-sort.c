#include <stdlib.h>
#include <stdio.h>

void selection_sort(int* L) {
    int length = sizeof(L)/sizeof(int);
    for(int i = 0; i < length; i++) {
        int min = L[i];
        for(int j=i; j< length; j++) {
            if(L[j] < min) {
                int tmp = min;
                min = L[j];
                L[j] = tmp;
            }
        }
        L[i] = min;
    }
}
int main(int argc, char** argv) {
    int nums[] = {9,8,6,5,4,3,2,1};
    selection_sort(nums);
    for(int i=0; i<sizeof(nums)/sizeof(int); i++) {
        printf("%d, ", nums[i]);
    } 
    printf("\n");
    return 0;
}
