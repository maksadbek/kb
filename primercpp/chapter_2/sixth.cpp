#include <iostream>
using namespace std;

void buildTime(int hours, int minutes){
    if(hours > 24){
        cerr<<"are you fucking with me???"<<endl;
        return;
    }
    cout<<"Time: "<<hours<<":"<<minutes<<endl;
}

int main(){
    int hours;
    int minutes;
    cout<<"Enter the number of hours: "; cin>>hours;
    cout<<"Enter the number of minutes: "; cin>>minutes;
    buildTime(hours, minutes);
    return 0;
}
