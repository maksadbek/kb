#include <iostream>
using namespace std;

struct CandyBar {
    char BrandName[80];
    float Weight;
    int Calories;
};

int main(){
    struct CandyBar snack = {"Mocha Munch", 2.3, 350};
    cout<<"snack's brand is "<<snack.BrandName<<endl;
    cout<<"snack's weight is "<<snack.Weight<<endl;
    cout<<"snack's calories is "<<snack.Calories<<endl;
    return 0;
}
