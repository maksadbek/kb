#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int used[100];
int p[100];
vector<int> order;
vector<vector<int> > G;

void dfs(int s){
    used[s] = 1;
    for(size_t i = 0; i < G[s].size(); i++){
        int to = G[s][i];
        if(!used[to]){
            dfs(to);
        }
    }
    order.push_back(s);
}

int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        vector<int> m;
        int a;
        cin>>a;
        while(a != 0){
            m.push_back(a-1); 
            cin>>a;
        }
        G.push_back(m);
    }
    for(int i = 0; i < n; i++){
        if(!used[i]){
            dfs(i);
        }
    }

    reverse(order.begin(), order.end());
    for(int i = 0; i < order.size(); i++){
       cout<<order[i]+1<<" ";
    }
    return 0;
}
