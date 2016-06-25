#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


void sort(vector<int> &numbers) {
	for (int i = 1; i < numbers.size(); i++) {
		int j = i-1;
		int n = numbers[i];

		while( numbers[j] > n && j >= 0) {
			numbers[j+1] = numbers[j];
			j = j - 1;
		}
		numbers[j+1] = n;
	}
	return;
}

int MinMex(int numbers[]) {
	int result = 0;
	return result;
}

int main() {
	int n;
	cin>>n;
	vector<int> numbers;

	for (int i=0; i<n; i++) {
		int tmp;
		cin >> tmp;
		numbers.push_back(tmp);
	}

	sort(numbers);
	for ( int x: numbers) {
		cout << x << endl;
	}	

	return 0;
}
