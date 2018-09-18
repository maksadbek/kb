#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> order;
vector<int> used;
vector<int> d, p;

void bfs(vector<vector<int> > G, int s){
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int i= 0; i<G[v].size(); i++){
            int to = G[v][i];
            if(!used[to]){
                used[to] = 1;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }
}


int main(){
    int n, s;
    cin>>n>>s;
    p.resize(n); 
    d.resize(n);
    used.resize(n);

    p[0] = -1;
    n -= 1;
    vector<vector<int> > G;
    for(int i=0; i<n; i++){
        vector<int> g;
        int t; cin>>t;
        g.push_back(i+t);
        G.push_back(g);
    }
    vector<int> g;
    g.push_back(n);
    G.push_back(g);
    
    bfs(G, 0);
    if(!used[s-1]){
        cout<<"NO";
    } else {
        cout<<"YES";
    }
    return 0;
}
