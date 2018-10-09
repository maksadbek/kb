#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using std::cout;
using std::vector;
using std::pair;
using std::make_pair;
using std::endl;
using std::max;

int knapsack_w_repetitions(vector<pair<int, int>> n, int w) {
        // w_tbl is a table stores the maximum available value
        // for weight i where i is an index;
        vector<int> values(w+1);
        values[0] = 0;

        for(int i = 1; i <= w; i++) {
                values[i] = 0;
                for(int j = 0; j < n.size(); j++) {
                        if(n[j].second > i) {
                                continue;
                        }

                        // w - wi gives the value w/o wi weight
                        int val = values[i - n[j].second] + n[j].first;
                        // printf("i: %d, w: %d\n", i, val);
                        values[i] = max(values[i], val);
                }
        }

        return values[w];
}

int knapsack_wo_repetitions(vector<pair<int, int>> n, int w) {
        vector<vector<int>> values(n.size()+1, vector<int>(w+1, 0));

        for(int i = 1; i <= w; i++) {
                for(int j = 1; j <= n.size(); j++) {
                        // initially the optimal solution is prev one.
                        // printf(">>> i: %d, j: %d\n", i, j);
                        values[j][i] = values[j-1][i];
                        if(n[j-1].second > i) {
                                continue;
                        }

                        // find the difference weight: w = i-n[j].second
                        // find the optimal value for this weight using -1 number: val = values[w][j-1]
                        // add the current item's value: val + n[j].first
                        int val = values[j-1][i-n[j-1].second] + n[j-1].first;
                        values[j][i] = max(values[j][i], val);
                        printf("%d %d %d\n", i, val, values[j][i]);
                }
        }

        for(auto i: values) {
                for(auto j: i) {
                        cout << j << " ";
                }
                cout << endl;
        }

        return values[n.size()-1][w];
}

int main() {
        vector<pair<int, int>> pairs;

        pairs.push_back(make_pair(30,6));
        pairs.push_back(make_pair(14,3));
        pairs.push_back(make_pair(16,4));
        pairs.push_back(make_pair(9,2));

        int weight = 10;
        cout << "w repetitions: " << knapsack_w_repetitions(pairs, weight) << endl;
        cout << "w/o repetitions: " << knapsack_wo_repetitions(pairs, weight) << endl;


        return 0;
}
