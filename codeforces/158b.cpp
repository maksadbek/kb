#include <iostream>
using std::cin;
using std::cout;

int compute(int numbers[]){
    int n = numbers[3];
    if(numbers[2] != 0){
        if(numbers[2] > numbers[0]){
            n += numbers[0];
            numbers[2] = numbers[2] - numbers[0];
            numbers[0] = 0;
        } else if(numbers[0] == numbers[2]) {
            n += numbers[0];
            numbers[0] = 0;
            numbers[2] = 0;
        } else {
            n += numbers[2];
            numbers[0] = numbers[0] - numbers[2];
            numbers[2] = 0;
        }
    }

    while(numbers[0] != 0 && numbers[1] != 0){
        if(numbers[0] > 1){
            numbers[0] -= 2;
        }else{
            numbers[0] -= 1;
        }

        numbers[1] -= 1;
        n++;
    }
    n += numbers[0] / 4;
    // if #1 is less than 4 and more than 0, then add them in one car
    if(numbers[0] % 4 != 0){
        n++;
    }
    if(numbers[1] > 1){
        n += numbers[1] / 2;
        n += numbers[1] % 2;
    }else{
        n += numbers[1];
    }
    n += numbers[2];
    return n;
}

int main(){
    int ans;
    int n;
    int numbers[] = {0,0,0,0};
    cin>>n;
    for(int i = 0; i<n; i++){
        int num;
        cin>>num;
        switch(num){
            case 1:
                numbers[0] += 1;
                break;
            case 2:
                numbers[1] += 1;
                break;
            case 3:
                numbers[2] += 1;
                break;
            case 4:
                numbers[3] += 1;
                break;
            default:
                break;
        }
    }
    ans = compute(numbers);
    cout<<ans;
    return 0;
}
