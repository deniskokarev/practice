#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* https://leetcode.com/contest/weekly-contest-154/problems/critical-connections-in-a-network/ */
using namespace std;

class Solution {
	struct G {
		vector<int> ee; // edge contains -> vertex num or -1 when deleted. <-> edges are next to each other
		vector<vector<int>> vv; // points to ee
	};
	static void del_edges(G &g, vector<int> &del) {
		for (auto d:del)
			g.ee[d] = g.ee[d^1] = -1;
	}
	static int dfs(G &g, int root, int depth, int e, vector<int> &seen, vector<int> &del) {
		if (!seen[root]) {
			seen[root] = depth;
			int rc = INT_MAX;
			for (auto ce:g.vv[root]) {
				if (ce != (e^1)) { // don't go back over the same connection
					int node = dfs(g, g.ee[ce], depth+1, ce, seen, del);
					if (node < depth)
						del.push_back(e);
					rc = min(rc, node);
				}
			}
			seen[root] = INT_MAX;
			return rc;
		} else if (seen[root] < depth) {
			del.push_back(e);
		}
		return seen[root];
	}
	static G conn_to_graph(int n, const vector<vector<int>> &connections) {
		G g {vector<int>(connections.size()*2), vector<vector<int>>(n)};
		int i = 0;
		for (auto c:connections) {
			g.ee[i*2] = c[1];
			g.ee[i*2+1] = c[0];
			g.vv[c[0]].push_back(i*2);
			g.vv[c[1]].push_back(i*2+1);
			i++;
		}
		return g;
	}
public:
	static vector<vector<int>> criticalConnections(int n, const vector<vector<int>> &connections) {
		G g = conn_to_graph(n, connections);
		vector<int> seen(n);
		vector<int> del;
		for (int i=0; i<n; i++)
			dfs(g, i, 1, INT_MAX, seen, del);
		del_edges(g, del);
		vector<vector<int>> ans;
		for (int i=0; i<connections.size(); i++)
			if (g.ee[i*2] >= 0)
				ans.push_back(connections[i]);
		return ans;
	}
};

int main(int argc, char **argv) {
	vector<vector<int>> a0 = Solution::criticalConnections(2, {{0,1},{1,0}});
	for (auto a:a0)
		cerr << a[0] << ' ' << a[1] << endl;
	cerr << endl;
	vector<vector<int>> a1 = Solution::criticalConnections(4, {{0,1},{1,2},{2,0},{1,3}});
	for (auto a:a1)
		cerr << a[0] << ' ' << a[1] << endl;
	cerr << endl;
	vector<vector<int>> a2 = Solution::criticalConnections(6, {{0,1},{1,2},{2,0},{1,3},{3,4},{4,5},{5,3}});
	for (auto a:a2)
		cerr << a[0] << ' ' << a[1] << endl;
	cerr << endl;
	vector<vector<int>> a3 = Solution::criticalConnections(5, {{1,0},{2,0},{3,2},{4,2},{4,3},{3,0},{4,0}});
	for (auto a:a3)
		cerr << a[0] << ' ' << a[1] << endl;
	cerr << endl;	
	return 0;
}
