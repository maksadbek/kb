#include <iostream>
using namespace std;

double CelciusToFahrenheit(int celcius){
    return 1.8 * celcius + 32.0;
}

int main(){
    double celcius;
    cout<<"Please enter a Celcius value: ";
    cin>>celcius;
    cout<<celcius<<" degree Celcius is "<<CelciusToFahrenheit(celcius)<<" degrees Fahrenheit."<<endl;
}
