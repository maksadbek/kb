#include <iostream>
using namespace std;

const double inchFactor = 0.0833333;

int inchToFeet(int inch){
    return inch * inchFactor;
}

int main(){
    int height;
    cout<<"Enter your height in inches :_____\b\b\b\b\b";
    cin>>height;
    cout<<"Your heaight in feets is : "<<inchToFeet(height)<<endl;
    cout<<"good bye, have a nice day"<<endl;
    return 0;
}
