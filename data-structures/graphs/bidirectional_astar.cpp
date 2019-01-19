#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

const long long inf = numeric_limits<long long>::max() / 4;

class astar {
	vector<pair<int,int>> &coords;
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q[2];
	vector<long long> f[2];
	vector<long long> g[2];
	set<int> proc[2];
        vector<long long> estimates[2];

	const int forward = 0;
	const int backward = 1;

	vector<vector<vector<pair<int,int>>>> &adj;
  
	double estimate(int v1, int v2) {
		auto delta1 = pow(coords[v1].first - coords[v2].first, 2);
		auto delta2 = pow(coords[v1].second - coords[v2].second, 2);
		return sqrt(delta1 + delta2);
	}

	void calc_estimates(int s, int t) {
		for(int i = 0; i < adj[0].size(); i++) {
			auto e = (estimate(s, i) + estimate(i, t))/2;
			estimates[forward][i] = e;
			estimates[backward][i] = -e;
		}
	}

	double shortest_path(int s, int t) {
		int index = 0;
		if(proc[0].size() < proc[1].size()) {
			index = 1;
		}
		
		for(auto x: proc[!index]) {
			proc[index].insert(x);
		}
		
		auto dist = inf;
		for(int i : proc[index]) {
			long long new_dist = g[0][i] + g[1][i];
			if(new_dist < dist) {
				dist = new_dist;
			}
		}

		if(dist==inf) {
			return -1;
		}
				
		
		return dist;
	}

	void visit(int side, int u, int s, int t) {
		for(auto &v: adj[side][u]) {
			auto neighbor = v.first;
			auto cost = g[side][u] + v.second;
			if(cost < g[side][neighbor]) {
				g[side][neighbor] = cost;
				auto heur_cost = estimates[side][neighbor] + cost;
				f[side][neighbor] = heur_cost;
				q[side].push(make_pair(heur_cost, neighbor));
			}
		}
	}

	int pop_and_relax(int side, int s, int t) {
		if(q[side].empty()) {
			return 0;
		}

		auto u = q[side].top();
		q[side].pop();

		// if this node was processed earlier, skip it.
		if(proc[side].find(u.second) != proc[side].end()) {
			return 0;
		}
		
		visit(side, u.second, s, t);
                proc[side].insert(u.second);
                
		if(proc[!side].find(u.second) != proc[!side].end()) {
			return 1;
		}

		return 0;
	}

	void init() {
		g[forward].resize(adj[forward].size(), inf);
		g[backward].resize(adj[forward].size(), inf);

		f[forward].resize(adj[forward].size(), 0);
		f[backward].resize(adj[forward].size(), 0);

		estimates[forward].resize(adj[forward].size());
		estimates[backward].resize(adj[forward].size());
	}

	void clear() {
		g[forward].assign(adj[forward].size(), inf);
		g[backward].assign(adj[forward].size(), inf);

		f[forward].assign(adj[forward].size(), 0);
		f[backward].assign(adj[forward].size(), 0);

		q[forward] = priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>>();
		q[backward] = priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>>();

		proc[forward].clear();
		proc[backward].clear();
	}
public:
	astar(vector<vector<vector<pair<int,int>>>> &graph, vector<pair<int,int>> &coords): coords(coords), adj(graph) {
		init();

		g[0].reserve(adj[0].size());
		g[0].reserve(adj[0].size());

		f[0].reserve(adj[0].size());
		f[0].reserve(adj[0].size());
	};
  
	// run returns the shortest path.
	long long query(int s, int t) {
		if(s == t) {
			return 0;
		}

		clear();
		calc_estimates(s, t);
		
		g[forward][s] = 0;
		f[forward][s] = 0;
		q[forward].push(make_pair(0, s));

		g[backward][t] = 0;
		f[backward][t] = 0;
		q[backward].push(make_pair(0, t));

		int i = 0;
		while(!q[forward].empty() or !q[backward].empty()) {
			i++;
			int forward_result = pop_and_relax(forward, s, t);
			if(forward_result < 0) {
				return -1;
			}

			if(forward_result == 1) {
				printf("i = %d\n", i);
				return shortest_path(s, t);
			}

			int backward_result = pop_and_relax(backward, s, t);
			if(backward_result < 0) {
				return -1;
			}

			if(backward_result == 1) {
				printf("i = %d\n", i);
				return shortest_path(s, t);
			}
		}

		return -1;
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	vector<pair<int,int>> coords(n);
	for (int i=0; i<n; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		coords[i] = make_pair(a,b);
	}

	vector<vector<vector<pair<int,int>>>> adj(2, vector<vector<pair<int,int>>>(n));
	for (int i=0; i<m; i++) {
		int u, v, c;
		
		scanf("%d%d%d", &u, &v, &c);
		adj[0][u-1].push_back(make_pair(v-1, c));
		adj[1][v-1].push_back(make_pair(u-1, c));
	}

	astar as(adj, coords);
	
	int t;
	scanf("%d", &t);
	for (int i=0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%lld\n", as.query(u-1, v-1));
	}

	return 0;
}
