#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::queue;
using std::reverse;

const int N = 100;
vector<int> d(N), p(N);
int used[100];
void bfs(int *G[], int n, int s){
    queue<int> q;
    q.push(s);
    used[s] = 1;
    p[s] = -1;
    while(!q.empty()){
       int v = q.front(); q.pop(); 
       for(int i =0; i< sizeof(*G[v] / sizeof(int)); i++){
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

void show_path(int to){
    if (!used[to]) {
        cout << "No path!";
    } else {
        vector<int> path;
        for (int v=to; v!=-1; v=p[v]){
            path.push_back (v);
        }
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (size_t i=0; i<path.size(); ++i){
            cout << path[i] + 1 << " ";
        }
    }
}

int main(){
    int N,M; 
    cin>>N>>M;
    int G[100][100];
    for(int i = 0; i < N; i++){
        for(int l = 0; l < M; l++){
            G[i][l] = -1;
        }
    }
    d.resize(N*M);
    p.resize(N*M);

    for(int n = 0; n < N*M; n++){
        G[n][M+n] = 1;
        G[n][n-M] = 1;
        G[n][n-1] = 1;
        G[n][n+1] = 1;
    }
    for(int n = 0; n < N*M; n++){
        cout<<n<<","<<M+n<<"# "<<G[n][M+n]<<endl;
        cout<<n<<","<<n-M<<"# "<<G[n][n-M]<<endl;
        cout<<n<<","<<n+1<<"# "<<G[n][n+1]<<endl;
        cout<<n<<","<<n-1<<"# "<<G[n][n-1]<<endl;
    }
    /*
    int start;
    cin>>start;
    bfs(start);

    for(int i =0; i < N*M; i++){
        cout<<"path to "<<i<<" ";
        show_path(i);
        cout<<endl;
    }
    */
    return 0;
}
