#include <iostream>
using namespace std;

int main(){
    double astroUnits, lightYears;
    cout<<"Enter the number of light years: ";
    cin>>lightYears;

    astroUnits = lightYears * 63.240;
    cout<<lightYears<<" light years = "<<astroUnits<<" astronomical units"<<endl;
    return 0;
}

