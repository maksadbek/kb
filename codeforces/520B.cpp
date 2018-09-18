#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 1e4 + 10;
vector<int> p(maxn),d(maxn);
vector<int> G[maxn];
int used[maxn];

void bfs(int s){
    queue<int> q;
    q.push(s);
    used[s] = 1;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(int to : G[v]){
            if(!used[to]){
                q.push(to);
                used[to] = 1;
                p[to] = v;
                d[to] = d[v] + 1;
            }
        }
    }
}

void show_path(int to){
    if(!used[to]){
        cout<<"NO";
    } else {
        vector<int> path;
        for(int v=to; v != -1; v=p[v]){
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for(int i = 0; i<path.size(); ++i){
            cout<<path[i]+1<<" ";
        }
    }
}

int main(){
    int n,m;
    p[0] = -1;
    cin>>n>>m;
    for(int i = 1; i<maxn; i++){
        vector<int> g;
        G[i].push_back(i-1);
        if(i*2 < maxn){
            G[i].push_back(i*2);
        }
    }

    bfs(n);
    cout<<d[m];
    return 0;
}
