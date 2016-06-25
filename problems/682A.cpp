#include <iostream>

using std::cin;
using std::cout;
using std::endl;


void calculate(int a, int b) {
	unsigned long long int result = 0;
	unsigned long long aa[5] = {0,0,0,0,0};
	unsigned long long bb[5] = {0,0,0,0,0};

	for (long i = 1; i <= a; i++) {
		int tmp = i%5;
		aa[tmp] += 1;
	}
	for (int i = 1; i <= b; i++) {
		int tmp = i%5;
		bb[tmp] += 1;
	}

	result += aa[0] * bb[0];
	result += aa[1] * bb[4];
       	result += aa[2] * bb[3];
      	result += aa[3] * bb[2];
      	result += aa[4] * bb[1];

	cout << result;
	return;
}

int main() {
	int a,b;
	cin >> a >> b;
	calculate(a,b);
	return 0;
}