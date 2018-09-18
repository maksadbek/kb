#include <iostream>
#include <string>
using namespace std;

int main(){
    string name, dessert;
    cout<<"Enter your name:\n";
    cin>>name;

    cout<<"Enter your favourite dessert:\n";
    cin>>dessert;

    cout << "I have some delicious " << dessert;
    cout <<" for you, "<<name<<".\n";
    return 0;
}
