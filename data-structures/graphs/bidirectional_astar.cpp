// Yes, it is ugly, but passes all test cases.

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

const long long inf = numeric_limits<int>::max() / 4;
typedef priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;

vector<pair<long long,long long>> coords;
vector<vector<pair<int,int>>> adj[2];

int n, m;

double estimate(int v1, int v2) {
        auto delta1 = coords[v1].first - coords[v2].first;
        auto delta2 = coords[v1].second - coords[v2].second;
        return sqrt(delta1*delta1 + delta2*delta2);
}

pq q[2];
vector<long long> g[2];
vector<bool> visited[2];

void init() {
        g[0].assign(n, inf);
        g[1].assign(n, inf);
        
        visited[0].assign(n, false);
        visited[1].assign(n, false);
}

long long query(int s, int t) {
        init();

        q[0] = pq();
        q[1] = pq();
        
        q[1].push(make_pair(0, t));
        g[0][s] = 0;

        q[0].push(make_pair(0, s));
        g[1][t] = 0;

        while(true) {
                if(q[0].empty()) {
                        break;
                }
        		
                auto u = q[0].top().second;
                q[0].pop();
                
                if(!visited[0][u]) {
                        visited[0][u] = true;
                        for(auto &v: adj[0][u]) {
                                auto neighbor = v.first;
                                auto cost = g[0][u] + v.second;
                                if(cost < g[0][neighbor] and !visited[0][neighbor]) {
                                        g[0][neighbor] = cost;
                                        auto est = estimate(t, neighbor) - estimate(neighbor, s);
                                        auto heur_cost = cost + est/2;
                                        q[0].push(make_pair(heur_cost, neighbor));
                                }
                        }

                        if(visited[1][u]) {
                                break;
                        }
                }
                
                if(q[1].empty()) {
                        break;
                }
        		
                auto b = q[1].top().second;
                q[1].pop();
      
                if(!visited[1][b]) {
                        visited[1][b] = true;
                        for(auto &v: adj[1][b]) {
                                auto neighbor = v.first;
                                auto cost = g[1][b] + v.second;
                                if(cost < g[1][neighbor] and !visited[1][neighbor]) {
                                        g[1][neighbor] = cost;
                                        auto est = estimate(s, neighbor) - estimate(neighbor, t);
                                        auto heur_cost = cost + est/2;
                                        q[1].push(make_pair(heur_cost, neighbor));
                                }
                        }

                        if(visited[0][b]) {
                                break;
                        }
                }
        }
                
        set<int> proc;
        for(int i = 0; i < n; i++) {
                if(visited[0][i]) {
                        proc.insert(i);
                }
        
                if(visited[1][i]) {
                        proc.insert(i);
                }
        }
        
        int best;
        auto dist = inf;
        for(int i : proc) {
                long long new_dist = g[0][i] + g[1][i];
                if(new_dist < dist) {
                        best = i;
                        dist = new_dist;
                }
        }
	
        if(dist==inf) {
                return -1;
        }
        
        return dist;
}


int main() {        
        scanf("%d%d", &n, &m);

        coords.resize(n);
        adj[0] = vector<vector<pair<int,int>>>(n);
        adj[1] = vector<vector<pair<int,int>>>(n);

        for (int i=0; i<n; i++){
                int a, b;
                scanf("%d%d", &a, &b);
                coords[i] = make_pair(a,b);
        }

        for (int i=0; i<m; i++) {
                int u, v, c;
                scanf("%d%d%d", &u, &v, &c);
                adj[0][u-1].push_back(make_pair(v-1, c));
                adj[1][v-1].push_back(make_pair(u-1, c));
        }

        int t;
        scanf("%d", &t);
        for (int i=0; i<t; ++i) {
                int u, v;
                scanf("%d%d", &u, &v);
                if(u==v) {
                        printf("0\n");
                        continue;
                }

                printf("%lld\n", query(u-1, v-1));
        }

        return 0;
}
