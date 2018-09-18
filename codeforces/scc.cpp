#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int p[100];
vector<int> used;
vector<int> order;
vector<vector<int> > g;
vector<vector<int> > gT;
vector<int> f;
vector<int> components;
int finished_time = 0;

void dfs(int s){
    finished_time++;
    used[s] = 1;
    for(size_t i = 0; i < g[s].size(); i++){
        int to = g[s][i];
        if(!used[to]){
            dfs(to);
        }
    }
    finished_time++;
    f[s] = finished_time;
    order.push_back(s);
}

// dfs for finding components
void dfs_comp(int s, int n){
    used[s] = 1;
    for(size_t i = 0; i < gT[s].size(); i++){
        int to = gT[s][i];
        if(!used[to]){
            dfs_comp(to, n);
        }
    }
    cout<<n<<" : "<<s+1<<endl;
}
int main(){
    int n;
    cin>>n;
    f.resize(n);
    gT.resize(n);
    used.resize(n);
    components.resize(n);

    for(int i=0; i<n; i++){
        vector<int> m;
        int a;
        cin>>a;
        while(a != 0){
            m.push_back(a-1); 
            gT[a-1].push_back(i); // fill transposed of g
            cin>>a;
        }
        g.push_back(m);
    }
    for(int i = 0; i < n; i++){
        if(!used[i]){
            dfs(i);
        }
    }

    for(int i = 0; i < n; i++){
        used[i] = 0;
    }

    reverse(order.begin(), order.end());
    int num=0;
    for(int i = 0; i < order.size(); i++){
        // cout<<order[i]+1<<" ";
        int v = order[i];
        if(!used[i]){
            dfs_comp(v, num++);
        }
    }

    // print finish time of nodes
    cout<<endl<<"------------"<<endl;
    for(int i = 0; i < f.size(); i++){
       cout<<f[i]<<" ";
    }
    return 0;
}
