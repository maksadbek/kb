#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

struct vertex {
	double g;
	double h;
	double f;

	int c;
	int index;
};

typedef vector<vector<vertex>> graph;

const int inf = numeric_limits<int>::max();

class min_heap {
public:
	min_heap() {}
	
	min_heap(vector<vertex> data): data(data) {
		for(int i = ceil(data.size()/2-1); i >= 0 ; i--) {
			sift_down(i);
		}
	}

	int push(vertex v) {
		data.push_back(v);
		return sift_up(data.size()-1);
	}

	vertex pop() {
		auto result = data[0];
		data[0] = data.back();
		data.pop_back();

		sift_down(0);

		return result;
	}

	bool empty() {
		return data.size() == 0;
	}

	void clear() {
		data.clear();
	}
	
private:
	vector<vertex> data;
	
	bool less(int v1, int v2) {
		return data[v1].f < data[v2].f;
	};

	int parent(int node) {
		if(node == 0) {
			return 0;
		}

		return std::ceil(float(node) / float(2)) - 1;
	}

	int left_child(int node) {
		return node * 2 + 1;
	}

	int right_child(int node) {
		return node * 2 + 2;
	}

	// sift_up moves up the node until his parent is not greater than him
	// or it does not reach the root.
	int sift_up(int node) {
		while(node >= 0 and less(node, parent(node))) {
			swap(data[parent(node)], data[node]);
			node = parent(node);
		}

		return node;
	}

	// sift_down move the node down until its right and light children are lower
	// than him.
	int sift_down(int node) {
		int min_index = node;

		int l = left_child(node);
		while(l < data.size() and less(l, min_index)) {
			min_index = l;
		}

		int r = right_child(node);
		while(r < data.size() and less(r, min_index)) {
			min_index = r;
		}

		if(data[min_index].index != data[node].index) {
			swap(data[min_index], data[node]);
			sift_down(min_index);
		}

		return min_index;
	}
};

class astar {
	graph &g;
	min_heap q;
	vector<bool> used;
	vector<pair<int,int>> &coords;
	
	double heuristic_potential(int v1, int v2) {
		auto delta1 = pow(coords[v1].first - coords[v2].first, 2);
		auto delta2 = pow(coords[v1].second - coords[v2].second, 2);
		return sqrt(delta1 + delta2);
	}

public:
	astar(graph &g, vector<pair<int,int>> &coords): g(g), coords(coords) {
		init();
	};

	// initialize computes the potential distances of vertexes.
	void init() {
		for(int i = 0; i < g.size(); i++) {
			for(auto &v : g[i]) {
				v.g = inf;
			}
		}
		
		used.resize(g.size(), false);
	}

	void clear() {
		used.assign(g.size(), false);
		q.clear();
		for(int i = 0; i < g.size(); i++) {
			for(auto &v : g[i]) {
				v.g = inf;
				v.f = 0;
				v.h = 0;
			}
		}
	}
	
	// run returns the shortest path.
	double query(int s, int t) {
		clear();
		
		if(s == t) {
			return 0;
		}
		
		vertex source;
		source.g = 0;
		source.h = 0;
		source.f = 0;
		source.index = s;
		q.push(source);

		while(!q.empty()) {
			auto u = q.pop();

			if(u.index == t) {
				return u.g;
			}

			if(used[u.index]) {
				continue;
			}

			used[u.index] = true;

			for(auto &v: g[u.index]) {
				if(u.g + v.c < v.g) {
					v.g = u.g + v.c;
					v.h = heuristic_potential(u.index, v.index);
					v.f = v.g + v.h;

					q.push(v);
				}
			}
		}

		return -1;
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	graph g(n);
	vector<pair<int,int>> coords(n);
	
	for (int i=0; i<n; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		coords[i] = make_pair(x, y);
	}
	
	for (int i = 0; i < m; i++) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);

		vertex vertex;
		vertex.c = c;
		vertex.index = v-1;
		
		g[u-1].push_back(vertex);
	}

	printf("got inputs\n");
	astar astar(g, coords);

	int t;
	scanf("%d", &t);
	for (int i=0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%f\n", astar.query(u-1, v-1));
	}
}
