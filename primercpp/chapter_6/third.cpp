#include <iostream>
#include <string>

using namespace std;

bool check(char chars[], char ch, const int n){
    for(int i =0; i < n; i++){
        if(chars[i] == ch){
            return true;
        }
    }
    return false;
}

int main(){
    const int N = 4;
    char variants[N] = {'a','b','c','d'};
    string question = "please enter one of the choices\n a, b, c or d";
    cout<<question<<endl;
    char answer;

    cin.get(answer);
    while(!check(variants, answer, N)){
        cout<<question<<endl;
        cin.get(answer);
    }

    switch(answer) {
        case 'a':
            cout<<"you chose a"<<endl;
            break;
        case 'b':
            cout<<"you chose b"<<endl;
            break;
        case 'c':
            cout<<"you chose c"<<endl;
            break;
        case 'd':
            cout<<"you chose d"<<endl;
            break;
        default:
            break;
    }
}
