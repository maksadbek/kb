#include <iostream>
#include <cstring>
using namespace std;

struct CandyBar {
    char BrandName[80];
    float Weight;
    int Calories;
};

int main(){
    int len = 3;
    struct CandyBar *snacks = new CandyBar[len];
    strcpy(snacks[0].BrandName,"Mocha Munch");
    snacks[0].Weight = 2.3;
    snacks[0].Calories = 350;

    strcpy(snacks[1].BrandName,"Choco Pie");
    snacks[1].Weight = 2.0;
    snacks[1].Calories = 377;

    strcpy(snacks[2].BrandName,"Mamba");
    snacks[2].Weight = 2.0;
    snacks[2].Calories = 377;

    for(int i=0; i<len; i++){
        cout<<snacks[i].BrandName<<endl;
        cout<<snacks[i].Weight<<endl;
        cout<<snacks[i].Calories<<endl;
    }
    return 0;
}
