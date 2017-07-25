#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/* CodeForces CF816C problem */
using namespace std;

struct G {
	int n;
	int r, c;
	bool operator<(const G &b) const {
		return n*10000+r*100+c > b.n*10000+b.r*100+b.c;
	}
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<G>> gg(n, vector<G>(m));
	set<G> mgg;
	for (int r=0; r<n; r++) {
		for (int c=0; c<m; c++) {
			int g;
			cin >> g;
			gg[r][c] = {g, r, c};
			mgg.insert(gg[r][c]);
		}
	}
	vector<pair<string,int>> plan;
	while (mgg.size() > 0 && mgg.begin()->n > 0) {
		G e = *mgg.begin();
		if (n>m) {
			int r;
			// try column
			for (r=0; r<n; r++)
				if (gg[r][e.c].n <= 0)
					break;
			if (r < n) {
				// try row
				int c;
				for (c=0; c<m; c++)
					if (gg[e.r][c].n <= 0)
						break;
				if (c < m) {
					cout << -1 << endl;
					return 0;
				} else {
					plan.push_back(make_pair("row", e.r));
					for (c=0; c<m; c++) {
						mgg.erase(mgg.find(gg[e.r][c]));
						gg[e.r][c].n--;
						mgg.insert(gg[e.r][c]);
					}
				}
			} else {
				plan.push_back(make_pair("col", e.c));
				for (r=0; r<n; r++) {
					mgg.erase(mgg.find(gg[r][e.c]));
					gg[r][e.c].n--;
					mgg.insert(gg[r][e.c]);
				}
			}
		} else {
			// try row
			int c;
			for (c=0; c<m; c++)
				if (gg[e.r][c].n <= 0)
					break;
			if (c < m) {
				// try column
				int r;
				for (r=0; r<n; r++)
					if (gg[r][e.c].n <= 0)
						break;
				if (r < n) {
					cout << -1 << endl;
					return 0;
				} else {
					plan.push_back(make_pair("col", e.c));
					for (r=0; r<n; r++) {
						mgg.erase(mgg.find(gg[r][e.c]));
						gg[r][e.c].n--;
						mgg.insert(gg[r][e.c]);
					}
				}
			} else {
				plan.push_back(make_pair("row", e.r));
				for (c=0; c<m; c++) {
					mgg.erase(mgg.find(gg[e.r][c]));
					gg[e.r][c].n--;
					mgg.insert(gg[e.r][c]);
				}
			}
		}
	}
	cout << plan.size() << endl;
	for (auto &a:plan)
		cout << a.first << " " << a.second+1 << endl;
	return 0;
}
