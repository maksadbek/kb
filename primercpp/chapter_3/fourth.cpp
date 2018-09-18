#include <iostream>
using namespace std;

const int dayFactor = 60*60*24;
const int minuteFactor = 60;
int main(){
    int seconds;
    int days;
    int minutes;
    cout<<"enter seconds: ";
    cin>>seconds;
    days = seconds / dayFactor;
    minutes = (seconds % dayFactor) / minuteFactor;
    seconds = (seconds % dayFactor) % minuteFactor;
    cout<<seconds<<" are "<<days<<" days and "<<minutes<<" minutes,"<<seconds<<" seconds."<<endl;
    return 0;
}
