#include "util.h"
void swap(int arr[], int a, int b) {
	int tmp = arr[b];
	arr[b]= arr[a];
	arr[a]= tmp;
	return;
}
