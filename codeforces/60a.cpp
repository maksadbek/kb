#include <iostream>
#include <queue>
#include <vector>

int bfs(vector<vector<int>> G, int s){
    int cells = 0;
    queue<int> q;
    bool used[N];
    q.push(s);
    used[0] = true;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for(size_t i = 0; i < G[v].size(); i++){
            int to = G[v][i];
            if(!used[to]){
                used[to] = true;
                q.push(to);
                cells++;
            }
        }
    }
}

int main(){
    
}
