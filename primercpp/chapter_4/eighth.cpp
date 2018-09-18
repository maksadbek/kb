#include <iostream>
using namespace std;

struct Pizza {
    char Company[80];
    int Diameter;
    int Weight;
};

int main(){
    struct Pizza *pizza = new Pizza;
    cout<<"enter the company name: ";
    cin.getline(pizza->Company, 80);

    cout<<"enter the pizza diameter: ";
    cin>>pizza->Diameter;

    cout<<"enter the pizza weight: ";
    cin>>pizza->Weight;

    cout<<"pizza company is: "<<pizza->Company<<endl;
    cout<<"pizza diamter is: "<<pizza->Diameter<<endl;
    cout<<"pizza weight is: "<<pizza->Weight<<endl;
    return 0;
}
