#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, int> llp;
typedef vector<vector<llp>> graph;
typedef priority_queue<llp, vector<llp>, greater<llp>> pqueue;

const ll inf = numeric_limits<ll>::max()/4;

struct Bidijkstra {
  graph adjs[2];
  pqueue q[2];
  vector<ll> dist[2];

  vector<int> prev[2];
  set<int> proc;
  vector<bool> visited[2];

  Bidijkstra(graph &adj, graph r_adj) {
    adjs[0] = adj;
    adjs[1] = r_adj;

    // printf("adj[1][0] size: %lu\n", adjs[0][0].size());
    
    dist[0].resize(adj.size(), inf);
    dist[1].resize(adj.size(), inf);

    prev[0].resize(adj.size());
    prev[1].resize(adj.size());

    visited[0].resize(adj.size(), false);
    visited[1].resize(adj.size(), false);
  }

  ll shortest_path(int s, int t) {
    ll d = inf;
    int best = -1;
    for(auto u : proc) {
      if(dist[0][u] + dist[1][u] < d) {
	best = u;
	d = dist[0][u] + dist[1][u];
      }
    }
    
    if(d == inf) {
      return -1;
    }

    /* no need to get paths
    vector<int> path;
    int last = best;
    while(last != s) {
      path.push_back(last);
      last = prev[0][last];
    }
    reverse(path.begin(), path.end());
    
    last = best;

    while(last != t) {
      last = prev[1][last];
      path.push_back(last);
    }
    */
					    
    return d;
  }

  ll visit(int side, int s, int t) {
    if(q[side].empty()) {
      return -1;
    }
    auto u = q[side].top();
    q[side].pop();

    if(u.first == inf) {
      return -2;
    }

    if(visited[side][u.second]) {
      return -2;
    }

    visited[side][u.second] = true;

    for(auto next : adjs[side][u.second]) {
      auto w = next.first;
      auto v = next.second;

      if(u.first + w < dist[side][v]) {
	dist[side][v] = dist[side][u.second] + w;
	q[side].push(make_pair(dist[side][v], v));
	prev[side][v] = u.second;
      }
    }

    if(!proc.insert(u.second).second) {
      return shortest_path(s, t);
    }

    return -2;
  }

  void clear() {
    q[0] = pqueue();
    q[1] = pqueue();
    proc.clear();
    prev[0].clear();
    prev[1].clear();

    dist[0].assign(adjs[0].size(), inf);
    dist[1].assign(adjs[0].size(), inf);

    visited[0].assign(adjs[0].size(), false);
    visited[1].assign(adjs[0].size(), false);
  }
  
  ll query(int s, int t) {
    clear();
    
    dist[0][s] = 0;
    dist[1][t] = 0;

    q[0].push(make_pair(0, s));
    q[1].push(make_pair(0, t));

    while(true) {
      auto d = visit(0, s, t);
      if(d != -2) {
	return d;
      }

      auto d_r = visit(1, s, t);
      if(d_r != -2) {
	return d_r;
      }
    }

    return -1;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
	
  graph adj(n);
  graph r_adj(n);
	
  for (int i=0; i<m; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
		
    adj[u-1].push_back(make_pair(c, v-1));
    r_adj[v-1].push_back(make_pair(c, u-1));
  }

  Bidijkstra bidijkstra(adj, r_adj);
  
  int t;
  scanf("%d", &t);
  for (int i=0; i < t; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%lld\n", bidijkstra.query(u-1, v-1));
  }
}
