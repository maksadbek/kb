#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

bool used[100];
vector<int> p;

void dfs-visit(vector<vector<int> > G, int s){
    stack<int> st;
    st.push(s);
    used[s] = true;
    while(!st.empty()){
        int v = st.top(); st.pop();
        for(size_t i = 0; i < G[v].size(); i++){
            int to = G[v][i];
            if(!used[to]){
                used[to] = true;
                st.push(to);
            }
        }
    }
}

void dfs(vector<vector<int> > G){
    for(int i=0; i < G.size(); i++){
    }
}


int main(){
    vector<vector<int> > G;
    int n,a;
    cin>>n;
    for(int i=0; i < n; i++){
        vector<int> v;
        cin>>a;
        while(a != 0){
            v.push_back(a);
            cin>>a;
        }
        G.push_back(v);
    }
    for(int i = 0; i < G.size(); i++){
        if(!used[i]){
            dfs(G, i);
        }
    }
}
