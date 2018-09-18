#include <iostream>
using namespace std;

int main(){
        int liters, distance;
        cout<<"enter how much liter of petrol do you used: ";
        cin>>liters;

        cout<<"now enter how many kilometres did you drive: ";
        cin>>distance;

        cout<<"your drive has used "<<(liters/distance)*100<<" liters per 100 kilometer"<<endl;
        return 0;
}


