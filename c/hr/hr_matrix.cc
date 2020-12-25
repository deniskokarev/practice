// https://www.hackerrank.com/challenges/matrix/problem
#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

struct E {
	int to;
	int score;
};

struct R {
	bool mach;
	int mn_score;
};

R dfs_walk(long &sm, const vector<vector<E>> &gg, const vector<bool> &mach, int root, int par) {
	if (mach[root]) {
		for (const E &e:gg[root]) {
			if (e.to != par) {
				R rchld = dfs_walk(sm, gg, mach, e.to, root);
				if (rchld.mach)
					sm += min(rchld.mn_score, e.score);
			}
		}
		return {true, INT_MAX};
	} else {
		R mx {false, 0};
		for (const E &e:gg[root]) {
			if (e.to != par) {
				R rchld = dfs_walk(sm, gg, mach, e.to, root);
				if (rchld.mach) {
					if (!mx.mach) {
						mx = {true, min(rchld.mn_score, e.score)};
					} else {
						if (mx.mn_score < min(rchld.mn_score, e.score)) {
							sm += mx.mn_score;
							mx = {true, min(rchld.mn_score, e.score)};
						} else {
							sm += min(rchld.mn_score, e.score);
						}
					}
				}
			}
		}
		return mx;
	}
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<vector<E>> gg(n);
	vector<bool> mach(n);
	for (int i=0; i<n-1; i++) {
		int f, t, s;
		scanf("%d%d%d", &f, &t, &s);
		gg[f].push_back({t,s});
		gg[t].push_back({f,s});
	}
	for (int i=0; i<k; i++) {
		int id;
		scanf("%d", &id);
		mach[id] = true;
	}
	long sm = 0;
	dfs_walk(sm, gg, mach, 0, -1);
	printf("%ld\n", sm);
	return 0;
}

