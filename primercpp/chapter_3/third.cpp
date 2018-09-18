/* 
 * 60 arcsec = 1minute
 * 60 arcminute = 1degree
 */
#include <iostream>
using namespace std;
const double minuteDegree = 60;
const double secondDegree = 3600;

int main(){
    int degrees, minutes, seconds;
    double result; 
    cout<<"enter degrees: ";
    cin>>degrees;
    cout<<"enter minutes: ";
    cin>>minutes;
    cout<<"enter seconds: ";
    cin>>seconds;

    result = degrees + (double)minutes/minuteDegree + (double)seconds/secondDegree;
    cout<<degrees<<" degrees,"<<minutes<<" minutes,"<<seconds<<" seconds are "<<result;
    return 0;
}
