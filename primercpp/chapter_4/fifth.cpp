#include <iostream>
using namespace std;

struct CandyBar {
    char BrandName[80];
    float Weight;
    int Calories;
};

int main(){
    int len = 4;
    struct CandyBar snacks[] = { {"Mocha Munch", 2.3, 350},
                                {"Choco Pie", 2.0, 377},
                                {"Mamba", 7.3, 278},
                                {"Chupa-chups", 2.3, 350} };
    for(int i=0; i<len; i++){
        cout<<snacks[i].BrandName<<endl;
        cout<<snacks[i].Weight<<endl;
        cout<<snacks[i].Calories<<endl;
    }
    return 0;
}
