#include <iostream>
using namespace std;

int main(){
    long long totalPopulation, localPopulation;
    double percentage;
    cout<<"enter total population of the earth: ";
    cin>>totalPopulation;
    cout<<"enter the populcation of uzbekistan: ";
    cin>>localPopulation;
    percentage = (100*(double)localPopulation)/(double)totalPopulation;
    cout<<"your country's population is "<<(100*localPopulation)/totalPopulation<<" "<<" the percont of all countries"<<endl;
    return 0;
}
