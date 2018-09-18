#include <iostream>
using namespace std;

const int dayFactor = 60*60*24;
const int hoursFactor = 60*60;
const int minuteFactor = 60;

int main(){
    long long input;
    int days, hours, minutes, left;
    cout<<"enter seconds: ";
    cin>>input;

    days = input / dayFactor;
    left = input % dayFactor;

    hours = left / hoursFactor;
    left = left % hoursFactor;

    minutes = left / minuteFactor;
    left = left % minuteFactor;

    cout<<input<<" is "<<days<<" days,"<<hours<<" hours,"<<minutes<<" minutes,"<<left<<" seconds"<<endl;
    return 0;
}
