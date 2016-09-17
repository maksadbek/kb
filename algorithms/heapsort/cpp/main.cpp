#include "heap.h"
#include "priority_queue.h"
#include <iostream>

int main() {
	std::cout<<"start"<<std::endl;
	std::cout<< parent(15) << std::endl;
	int A[] = {4,1,3,2,16,9,10,14,8,7};

	int  max = heap_extract_max(A, 9);
	std::cout << "max element is: "<< max << std::endl;

	heapsort(A, 8);

	for (int i =0 ;i <= 9; i++ ) {
		std::cout<< A[i] << ", ";
	}
	std::cout<<std::endl;
}
