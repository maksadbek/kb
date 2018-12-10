#include <iostream>
#include <vector>
#include <stack>
#include <functional>

using std::vector;
using std::stack;

struct Graph {
        vector<vector<int>> adj;
        vector<bool> used;
        stack<int> path;
        vector<int> pre;
        vector<int> post;
        int counter = 0;

        Graph(vector<vector<int>> adj) {
                this->adj = adj;
                this->used.resize(adj.size());
                this->pre.resize(adj.size());
                this->post.resize(adj.size());

                for(int i = 0; i < adj.size(); i++) {
                        std::cout <<  i << ":";

                        for(int j =0; j< adj[i].size(); j++) {
                                std::cout << adj[i][j] << " ";
                        }

                        std::cout << std::endl;
                }
        }

        vector<int> tsort() {
                // clear path
                for(int i = 0; i < adj.size(); i++) {
                        if(!used[i]) {
                                dfs(i);
                        }
                }

                vector<int> p;
                while(!path.empty()) {
                        p.push_back(path.top());
                        path.pop();
                }

                return p;
        };

        void print_orders() {
                for(int i = 0; i < adj.size(); i++) {
                        std::cout << i << ": [" << pre[i] << ":" << post[i] << "]" << std::endl;
                }
        }

        void dfs(int i) {
                used[i] = true;

                pre[i] = counter++;
                for(int v = 0; v < adj[i].size(); v++) {
                        int to = adj[i][v];
                        if(!used[to]) {
                                dfs(to);
                        }
                }

                post[i] = counter++;
                path.push(i);
        };
};

int main() {
        int n, m;
        std::cin >> n >> m;

        vector<vector<int>> adj(n, vector<int>());
        vector<vector<int>> reversed_adj(n, vector<int>());

        for(int i = 0; i < m; i++) {
                int u, v;
                std::cin >> u >> v;

                adj[u].push_back(v);
                reversed_adj[v].push_back(u);
        }

        // dfs on the reversed graph.
	Graph* g = new Graph(reversed_adj);

	auto path = g->tsort();

        vector<vector<int>> components(adj.size(), vector<int>());
        vector<bool> visited(adj.size(), false);

        // dfs lambda
        std::function<void (int, int)> f;
        f = [&f, &adj, &components, &visited](int s, int c) {
        	components[c].push_back(s);
        	visited[s] = true;

                for(int i = 0; i < adj[s].size(); i++) {
                        int to = adj[s][i];
                        if(!visited[to]) {
                                f(to, c);
                        }
                }
        };

        int component_index = 0;
        for(int p : path) {
               if(!visited[p]) {
                       f(p, component_index);
               }

               component_index++;
        }

        for(int i = 0; i < components.size(); i++) {
                printf("component %d: ", i);
                for(int j = 0; j < components[i].size(); j++) {
                        printf("%d ", components[i][j]);
                }
                printf("\n");
        }

       	delete g;
        return 0;
}
