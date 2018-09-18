#include <iostream>
#include <vector>
using namespace std;

int main(){
    int numOfCand, max=0, maxIndex=0, result=0;
    vector<int> votes;


    cin>>numOfCand;

    for(int i=0; i<numOfCand; i++){
        int vote;
        cin>>vote;
        if(max < vote){
            max = vote;
            maxIndex = i;
        }
        votes.push_back(vote);
    }

    while(votes[0] < votes[maxIndex]){
        for(int i=1; i<numOfCand; i++){
            if(votes[i] != 0){
                if(votes[0] > votes[maxIndex]){
                    break;
                }
                votes[0] += 1;
                votes[i] -= 1;
                result++;
                cout<<i<<" "<<votes[i]<<endl;
                cout<<"Limak is: "<<votes[0]<<endl;
            }
        }
        cout<<endl;
    }
    cout<<result;
    return 0;
}
