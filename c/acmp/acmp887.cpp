/* ACMP 887 */
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(const vector<vector<int>> &mm, int node, vector<int> &log) {
	vector<pair<int,vector<int>>> ll(mm[node].size());
	int c = 0;
	for (int i:mm[node]) {
		ll[c].first = i;
		dfs(mm, i, ll[c].second);
		c++;
	}
	sort(ll.begin(), ll.end(), [](const pair<int, vector<int>> &a, const pair<int, vector<int>> &b) {return a.second.size()<b.second.size();});
	for (int i=0; i<(ll.size()+1)/2; i++) {
		vector<int> &l = ll[i].second;
		log.insert(log.end(), l.begin(), l.end());
	}
	log.push_back(node);
	return log.size();
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<vector<int>> mm(n);
	for (int r=0; r<n; r++) {
		int d;
		for (scanf("%d", &d); d; scanf("%d", &d))
			mm[r].push_back(d-1);
	}
	vector<int> log;
	dfs(mm, 0, log);
	printf("%d\n", (int)log.size());
	for (auto node:log)
		printf("%d\n", node+1);
	return 0;
}
