#include "heap.h"
#include <iostream>

int main() {
	std::cout<<"start"<<std::endl;
	std::cout<< parent(15) << std::endl;
	int A[] = {4,1,3,2,16,9,10,14,8,7};

	heapsort(A, 9);

	for (int i =0 ;i <= 9; i++ ) {
		std::cout<< A[i] << ", ";
	}
	std::cout<<std::endl;
}
