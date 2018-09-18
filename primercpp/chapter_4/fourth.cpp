#include <iostream>
#include <cstring>
using namespace std;

int main(){
    string firstName;
    string lastName;
    string fullName;
    cout<<"enter your first name: ";
    cin>>firstName;
    cout<<"enter your last name: ";
    cin>>lastName;

    fullName = firstName + ", " + lastName;
    cout<<"here is the information is a single string: "<<fullName;
    return 0;
}
