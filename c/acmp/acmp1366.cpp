/* ACMP 1366 */
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

struct P { // point
	int x, y;
};

struct V { // vector at point
	int dir;
	P p;
};

enum {E=0, S, W, N}; // direction

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

using D = array<int, 4>;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	string nl;
	getline(cin, nl);
	vector<string> map(n, string(m, 'X'));
	P start {0, 0}, finish {0, 0};
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			cin.get(map[i][j]);
			if (map[i][j] == 'S')
				start = {j, i};
			else if (map[i][j] == 'F')
				finish = {j, i};
		}
		getline(cin, nl);
	}
	int ans = INT_MAX;
	for (auto &s:{V {E, start}, V {W, start}}) { // start either towards E or W
		queue<V> qq;
		qq.push(s);
		vector<vector<D>> dist(n, vector<D>(m, {{INT_MAX, INT_MAX, INT_MAX, INT_MAX}}));
		dist[start.y][start.x] = {{0, 0, 0, 0}};
		while (!qq.empty()) {
			const V &v = qq.front();
			const int d = dist[v.p.y][v.p.x][v.dir];
			for (int dir=v.dir, i=0; i<2; dir++, dir&=3, i++) {
				const V nv = V {dir, P {v.p.x+moves[dir].x, v.p.y+moves[dir].y}};
				if (map[nv.p.y][nv.p.x] != 'X' && dist[nv.p.y][nv.p.x][dir] > d+1) {
					dist[nv.p.y][nv.p.x][dir] = d+1;
					qq.push(nv);
				}
			}
			qq.pop();
		}
		ans = min(ans, *min_element(dist[finish.y][finish.x].begin(), dist[finish.y][finish.x].end()));
	}
	cout << ans << endl;
	return 0;
}
