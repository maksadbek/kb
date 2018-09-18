#include <iostream>
using namespace std;

double meterFactor = 0.0254;
double kiloFactor = 2.2;
double inchFactor = 12;

double feetToInch(double feet){
    return inchFactor * feet;
}

double inchToMeter(double inch){
    return inch * meterFactor;
}

double poundsToKilo(double pounds){
    return pounds * kiloFactor;
}

double computeBMI(double height, double weight){
    return weight / (height * height);
}

int main(){
    double height;
    double weight;
    cout<<"enter you height in feet: ";
    cin>>height;

    cout<<"enter your weight in pounds: ";
    cin>>weight;


    cout<<"your BMI is: "<<computeBMI(inchToMeter(feetToInch(height)), poundsToKilo(height))<<endl;
    return 0;
}
