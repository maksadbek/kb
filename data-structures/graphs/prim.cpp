// Prims algorithm
// This program requires that input was a decart coordinates
// It is not guaranteed that it always works correctly.
// Implementation differs from the Cormen's book.
// It did not worked for my case. More precisely, the relaxation part worked wrong.

#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <queue>
#include <cmath>

using std::vector;
using std::pair;
using std::priority_queue;
using std::greater;
using std::numeric_limits;
using std::make_pair;
using std::pow;
using std::sqrt;

typedef pair<double, int> int_pair;

const double inf = numeric_limits<double>::max();

double point_distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double prim(vector<vector<int_pair>> adj, int s) {
	vector<bool> used(adj.size(), false);
	vector<double> dist(adj.size(), inf);
	dist[s] = 0;

	// min_dist is a minimum spanning tree length.
	double min_dist = 0;

	for(int i = 0; i < adj.size(); i++) {
		// This loop find the vertex with smallest weight
		// It can be replaced with Priority Queue.
		int cur = -1;
		for(int j = 0; j < dist.size(); j++) {
			// always choose a vertex that is not in the minimum spanning tree.
			if(used[j]) {
				continue;
			}
			
			if(cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}

		// add this vertex to minimum spanning tree.
		min_dist += dist[cur];
		
		// this it as used
		used[cur] = true;
		
		// discover adjacent vertexes and update their distances.
		for(auto const &v : adj[cur]) {
			double w = v.first;
			int to = v.second;
			
			// if it is not already in the mininum spanning tree
			// and distance to this vertex is less than what we already have.
			if(!used[to] and w < dist[to]) {
				dist[to] = w;
			}
		}
	}

	return min_dist;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}

	vector<vector<int_pair>> adj(n, vector<int_pair>());
	
	// range over points and find all distances
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) {
				continue;
			}


			double dist = point_distance(x[i], y[i], x[j], y[j]);
			adj[i].push_back(make_pair(dist, j));
		}
	}

	printf("%f", prim(adj, 0));
}
