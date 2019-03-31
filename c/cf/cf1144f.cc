#include <iostream>
#include <vector>
/* CodeForces CF1144F problem */
using namespace std;

struct E {
	int f, t;
	int orient;
};

void dfs(vector<vector<pair<E*,int>>> &gg, vector<E> &ee, vector<int> &seen, int root, int orient) {
	seen[root] = 1;
	for (auto &et:gg[root]) {
		if (et.first->orient == -1) {
			if (et.first->f == root)
				et.first->orient = orient;
			else
				et.first->orient = !orient;
		}
		if (!seen[et.second])
			dfs(gg, ee, seen, et.second, !orient);
	}
}

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<E> ee(m);
	vector<vector<pair<E*,int>>> gg(n+1);
	for (int i=0; i<m; i++) {
		auto &e = ee[i];
		cin >> e.f >> e.t;
		e.orient = -1;
		gg[e.f].push_back(make_pair(&ee[i], e.t));
		gg[e.t].push_back(make_pair(&ee[i], e.f));
	}
	vector<int> seen(n+1);
	dfs(gg, ee, seen, 1, 0);
	cout << "YES" << endl;
	for (auto &e:ee)
		cout << e.orient;
	cout << endl;
	return 0;
}
