/* ACMP 1054 */
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

struct P {
	int x, y;
};

const array<P, 4> dirs {{ P {1, 0}, P {0, 1}, P {-1, 0}, P {0, -1} }};

using D = array<int, 4>; // disance is direction-dependent

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<string> map(n+2, string(m+2, 'P'));
	P start {0, 0}, finish {0, 0};
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		for (int j=1; j<=m && j-1<s.length(); j++) {
			map[i][j] = s[j-1];
			if (map[i][j] == 'S')
				start = {j, i};
			else if (map[i][j] == 'F')
				finish = {j, i};
		}
	}
	vector<vector<D>> dist(n+2, vector<D>(m+2, D {{INT_MAX, INT_MAX, INT_MAX, INT_MAX}}));
	queue<P> qq;
	qq.push(start);
	map[start.y][start.x] = '.';
	dist[start.y][start.x] = {{1, 1, 1, 1}};
	while (qq.size() > 0) {
		const P &p = qq.front();
		const auto &d = dist[p.y][p.x];
		int pmn = *min_element(d.begin(), d.end());
		for (int dir=0; dir<dirs.size(); dir++) {
			const P np = P {p.x+dirs[dir].x, p.y+dirs[dir].y};
			int nd = min(dist[p.y][p.x][dir], pmn+1);
			if (map[np.y][np.x] != 'P' && dist[np.y][np.x][dir] > nd) {
				dist[np.y][np.x][dir] = nd;
				qq.push(np);
			}
		}
		qq.pop();
	}
	const auto &d = dist[finish.y][finish.x];
	int ans = *min_element(d.begin(), d.end());
	if (ans == INT_MAX)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}
