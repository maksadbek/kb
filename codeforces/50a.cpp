#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int count(int a, int b){
    int n;
    if(a % 2 == 0){
        n = (a / 2) * b;
    } else {
        int r = a % 2;
        n = (a / 2) * b;
        if(r * b >= 2){
            n += (r*b) / 2;
        }
    }
    return n;
}
int main(){
    int c;
    int M,N;
    cin>>M>>N;
    if(M > N){
        c = count(M,N);
    }
    c= count(N,M);
    cout<<c;
    return 0;
}
