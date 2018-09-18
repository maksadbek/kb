#include <iostream>
#include <cstring>
using namespace std;

int main(){
    int year;
    char str[100];
    string str1;
    string str2;
    cin>>year;
    cin.get();
    cin.get(str, 100).get();
    cout<<str;
    cin>>str1;
    strcpy(str, "hi ");
    cout<<str1;
    strcat(str, ", you're welcome");
    return 0;
}
    
