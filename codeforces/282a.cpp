#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int main(){
    string input;
    int n;
    int X = 0;
    std::size_t found;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>input;
        cout<<input;
        found = input.find("++");
        if(found != std::string::npos){
            X++;
        }
        found = input.find("--");
        if(found != std::string::npos){
            X--;
        }
    }
    cin>>input;
    return 0;
}
