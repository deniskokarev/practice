#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF977D problem */
using namespace std;

bool dfs(const vector<vector<int>> &mm, vector<int> &seen, int n, int start, int step) {
	if (step >= n)
		return true;
	for (int j=0; j<n; j++) {
		if (mm[start][j] && seen[j] == -1) {
			seen[j] = step;
			if (dfs(mm, seen, n, j, step+1))
				return true;
			seen[j] = -1;
		}
	}
	return false;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	vector<vector<int>> mm(n, vector<int>(n));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (aa[j]*3 == aa[i]) {
				mm[i][j] = 1;
			} else if (aa[i]*2 == aa[j]) {
				mm[i][j] = 1;
			}
		}
	}
	for (int i=0; i<n; i++) {
		vector<int> seen(n, -1);
		seen[i] = 0;
		if (dfs(mm, seen, n, i, 1)) {
			vector<pair<int, int64_t>> res(n);
			for (int k=0; k<n; k++)
				res[k] = make_pair(seen[k], aa[k]);
			sort(res.begin(), res.end());
			for (auto r:res)
				cout << r.second << ' ';
			cout << endl;
			return 0;
		}
	}
	cout << "no answer" << endl;
	return 0;
}
