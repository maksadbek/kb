#include <iostream>
#include <vector>

using namespace std;

// 1 2 3 4
// 2 1 3 4
void backtrack_subsets(vector<int> &a, int k, vector<int> &input) {
	if (k == input.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i]) {
				cout << input[i] << ", ";
			}
		}
		cout << endl;
	} else {
		a[k] = true;
		backtrack_subsets(a, k+1, input);

		a[k] = false;
		backtrack_subsets(a, k+1, input);
	}
}

void backtrack_permutations(vector<int> &a, int k, vector<int> &input) {
	if (k == input.size()) {
		for (int i : a) {
			cout << input[i] << ", ";
		}
		cout << endl;
	} else {
		vector<int> in_perm(a.size(), false);
		for(int i : a) {
			if (i >= 0) {
				in_perm[i] = true;
			}
		}

		for(int i = 0; i < input.size(); i++) {
			if (in_perm[i]) {
				continue;
			}

			a[k] = i;
			backtrack_permutations(a, k+1, input);
		}
	}
}

int main() {
	int n; cin >> n;

	vector<int> a(n, -1);
	vector<int> input(n);

	for(int i = 1; i < n+1; i++) {
		input[i-1] = i;
	}

//	backtrack_subsets(a, 0, input);
	backtrack_permutations(a, 0, input);

	return 0;
}
