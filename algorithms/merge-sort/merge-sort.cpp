#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int> &A, int p, int q, int r);
void Merge_Sort(vector<int> &A, int p, int r);

int main()
{
	vector<int> A(8);
	A[0] = 35;
	A[1] = 34;
	A[2] = 3;
	A[3] = 21;		
	A[4] = 123;
	A[5] = 1235;
	A[6] = 0;
	A[7] = -1;
	Merge_Sort(A, 0, A.size()-1);
	
	for(int i=0; i<A.size(); i++) cout << A[i] << " ";
					
	return 0;	
}

void Merge_Sort(vector<int> &A, int p,  int r) {
	if(p<r) {
		int q = (p+r)/2;
		Merge_Sort(A, p, q);
		Merge_Sort(A, q+1, r);
		Merge(A, p, q, r);
	}
}

void Merge(vector<int> &A, int p, int q, int r) {
	int n1 = q-p+1;
	int n2 = r-q;
	
	vector<int> L(n1);
	vector<int> R(n2);
	for(int i=0; i<n1; i++) {
		L[i] = A[p+i];
	}
	for(int j=0; j<n2; j++) {
		R[j] = A[q+j+1];
	}
	int i=0;
	int j=0;
	for(int k=p; k<=r; k++) {
		if(j==n2 && i<n1 || i<n1 && j<n2 && L[i]<=R[j]) {
			A[k] = L[i];
			i++;
		} else if(j<n2) {
			A[k] = R[j];
			j++;
		}
	}
}

