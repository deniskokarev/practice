/* ACMP 1362 */
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

enum {
	P_FREE = 0,	P_WALL,	P_HALL
};

enum {
	D_R = 0, D_D, D_L, D_U, D_SZ
};

struct B { // ball
	int x, y;
	int dir;
};

const array<B, D_SZ> dirs {{ B {1, 0, D_R}, B {0, 1, D_D}, B {-1, 0, D_L}, B {0, -1, D_U} }};

struct D { // distance
	int mnd;
	array<int, D_SZ> d; // disance is direction-dependent
};
	
int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> map(n+2, vector<int>(m+2, P_WALL));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			cin >> map[i][j];
	vector<vector<D>> dist(n+2, vector<D>(m+2, D {INT_MAX, {{INT_MAX, INT_MAX, INT_MAX, INT_MAX}}}));
	queue<B> qq;
	// start with 2 balls
	qq.push(B {1, 1, D_R});
	qq.push(B {1, 1, D_D});
	dist[1][1] = {1, {{1, 1, 1, 1}}};
	while (qq.size() > 0) {
		const B &p = qq.front();
		if (map[p.y][p.x] != P_WALL) {
			int dir = p.dir;
			const B np = B {p.x+dirs[dir].x, p.y+dirs[dir].y, dir};
			if (map[np.y][np.x] == P_WALL) {
				dist[p.y][p.x].mnd = min(dist[p.y][p.x].mnd, dist[p.y][p.x].d[dir]);
				// try to bounce into orthogonal direction 1
				int o1 = (dir+1)%D_SZ; 
				const B onp1 = B {p.x+dirs[o1].x, p.y+dirs[o1].y, o1};
				if (dist[onp1.y][onp1.x].d[o1] > dist[p.y][p.x].mnd+1) {
					dist[onp1.y][onp1.x].d[o1] = dist[p.y][p.x].mnd+1;
					qq.push(onp1);
				}
				// try to bounce into orthogonal direction 2
				int o2 = (dir+3)%D_SZ;
				const B onp2 = B {p.x+dirs[o2].x, p.y+dirs[o2].y, o2};
				if (dist[onp2.y][onp2.x].d[o2] > dist[p.y][p.x].mnd+1) {
					dist[onp2.y][onp2.x].d[o2] = dist[p.y][p.x].mnd+1;
					qq.push(onp2);
				}
			} else {
				// keep rolling
				if (dist[np.y][np.x].d[dir] > dist[p.y][p.x].d[dir]) {
					dist[np.y][np.x].mnd = min(dist[np.y][np.x].mnd, dist[p.y][p.x].mnd);
					dist[np.y][np.x].d[dir] = dist[p.y][p.x].d[dir];
					qq.push(np);
				}
			}
		}
		qq.pop();
	}
	int ans = INT_MAX;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			if (map[i][j] == P_HALL)
				ans = min(ans, dist[i][j].mnd);
	cout << ans << endl;
	return 0;
}
