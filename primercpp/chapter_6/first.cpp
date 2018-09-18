#include <iostream>
#include <cctype>

using namespace std;

int main(){
    char ch;
    do{
        cin.get(ch);
        if(isdigit((int)ch) == 0){
            cout<<ch;
        }

    }while(ch != '@');
    return 0;
}
