#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

int main(){
    int sizeOfA,sizeOfB,k,m;
    cin>>sizeOfA>>sizeOfB>>k>>m;
    bool result = true;
    vector<int> A;
    vector<int> B;

    for(int i = 0; i < sizeOfA; i++){
        int n; cin>>n;
        A.push_back(n);
    }

    for(int i = 0; i < sizeOfB; i++){
        int n; cin>>n;
        B.push_back(n);
    }
    
    for(int i = 0; i < k; i++){
        for(int l = 0; l < m; l++){
            if(A[i] >= B[l]){
               result = false; 
               break;
            }
        }
    }
    if(result){
        cout<<"YES";
    } else {
        cout<<"NO";
    }
    return 0;
}
