#include <iostream>
using std::cin;
using std::cout;

int main(){
    int n;
    int count = 0;
    cin>>n;
    for(int i=0; i<n; i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a + b + c > 1){
            count++;
        }
    }
    cout<<count;
}
