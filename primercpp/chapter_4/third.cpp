#include <iostream>
#include <cstring>
using namespace std;

int main(){
    int arrSize = 80;
    char *firstName = new char[arrSize];
    char *lastName = new char[arrSize];
    cout<<"enter your first name: ";
    cin.getline(firstName, 80);
    cout<<"enter your last name: ";
    cin.getline(lastName, 80);

    char *fullName = new char[strlen(firstName) + strlen(lastName) + 2];
    strcat(fullName, firstName);
    strcat(fullName, ", ");
    strcat(fullName, lastName);

    cout<<"here is the information is a single string: "<<fullName;
    return 0;
}
