/* ACMP 1376 */
#include <cstdio>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

struct N {
	int conn;
	int dist;
	int to;
	int to_id;
};

constexpr int DMAX = INT_MAX/2; // cannot get higher than that without loops
constexpr int DMIN = INT_MIN/2; // cannot get lower than that without loops

void append_path(vector<int> &path, const vector<vector<N>> &mm, int f, int t) {
	int cnt = 0;
	while (mm[f][t].to != t) {
		path.push_back(mm[f][t].to_id);
		f = mm[f][t].to;
		cnt++;
		assert(cnt < 1000 && "should be no loops");
	}
	path.push_back(mm[f][t].to_id);
}

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	vector<vector<N>> mm(n+1, vector<N>(n+1, N {0, 0, 0, 0}));
	for (int id=1; id<=m; id++) {
		int i, j;
		int d;
		scanf("%d %d %d", &i, &j, &d);
		mm[i][j] = N {1, d, j, id};
	}
	for (int twice:{0,1})
	for (int k=1; k<=n; k++) {
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=n; j++) {
				int ndist = mm[i][k].dist+mm[k][j].dist;
				if (ndist > DMAX)
					ndist = DMAX;
				if (ndist < DMIN)
					ndist = DMIN;
				if (mm[i][j].conn && mm[i][k].conn && mm[k][j].conn) {
					if (mm[i][j].dist < ndist)
						mm[i][j] = N {1, ndist, mm[i][k].to, mm[i][k].to_id};
				} else if (mm[i][k].conn && mm[k][j].conn) {
					mm[i][j] = N {1, ndist, mm[i][k].to, mm[i][k].to_id};
				}
			}
		}
	}
	for (int i=1; i<=n; i++)
		if (mm[i][i].dist > 0)
				mm[i][i].conn = 2; // pos loop detected
	bool inf = false;
	vector<int> path;
	int f, t;
	scanf("%d", &t);
	k--;
	while (k--) {
		f = t;
		scanf("%d", &t);
		if (mm[f][f].conn == 2 || mm[t][t].conn == 2) {
			inf = true;
			break;
		}
		append_path(path, mm, f, t);
	}
	if (!inf) {
		printf("%d\n", (int)path.size());
		for (auto p:path)
			printf("%d ", p);
		printf("\n");
	} else {
		printf("infinitely kind\n");
	}
	return 0;
}
