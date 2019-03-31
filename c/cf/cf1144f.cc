#include <iostream>
#include <vector>
#include <queue>
/* CodeForces CF1144F problem */
using namespace std;

struct E {
	int f, t;
	int orient;
};

struct Q {
	int node;
	int orient;
};

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
	queue<Q> qq; // node,orient
	qq.push(Q{1,0});
	seen[1] = 0;
	bool ans = true;
	while (!qq.empty()) {
		auto top = qq.front();
		qq.pop();
		for (auto &et:gg[top.node]) {
			if (!seen[et.second]) {
				seen[et.second] = 1;
				qq.push(Q {et.second, !top.orient});
			}
			int o = ((top.orient == 0) ^ (et.first->f == top.node));
			if (et.first->orient == -1)
				et.first->orient = o;
			ans &= (et.first->orient == o);
		}
	}
	if (ans) {
		cout << "YES" << endl;
		for (auto &e:ee)
			cout << e.orient;
		cout << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
