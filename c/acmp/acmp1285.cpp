/* ACMP 1285 */
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <queue>

using namespace std;

enum {
	H = 0, V = 1	// possible directions
};

using D = array<int, 2>; // distance is direction-sensitive

struct P {
	int x, y;
};

const array<array<P,2>,2> moves {{ {{ {1, 0}, {-1, 0} }}, {{ {0, 1}, {0, -1} }} }}; // moves in H and V directions

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<string> map(n+2, string(m+2, '#'));
	P start {1, 1}, end {1, 1};
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		for (int j=1; j<=m && j-1<s.length(); j++) {
			map[i][j] = s[j-1];
			if (s[j-1] == 'S')
				start = P {j, i};
			else if (s[j-1] == 'E')
				end = P {j, i};
			
		}
	}
	map[start.y][start.x] = map[end.y][end.x] = '.';
	vector<vector<D>> dist(n+2, vector<D>(m+2, {{INT_MAX-1, INT_MAX-1}}));
	dist[start.y][start.x] = {{0, 0}};
	queue<P> qq;
	qq.push(start);
	while (qq.size() > 0) {
		const P &p = qq.front();
		if (map[p.y][p.x] == '.') {
			int mnd = min(dist[p.y][p.x][H], dist[p.y][p.x][V]);
			for (int dir=0; dir<moves.size(); dir++) {
				for (auto &m:moves[dir]) {
					const P np {p.x+m.x, p.y+m.y};
					if (dist[np.y][np.x][dir] > mnd+1) {
						dist[np.y][np.x][dir] = mnd+1;
						qq.push(np);
					}
				}
			}
		} else if (map[p.y][p.x] == 'B') {
			for (int dir=0; dir<moves.size(); dir++) {
				for (auto &m:moves[dir]) {
					const P np {p.x+m.x, p.y+m.y};
					if (dist[np.y][np.x][dir] > dist[p.y][p.x][dir]+1) {
						dist[np.y][np.x][dir] = dist[p.y][p.x][dir]+1;
						qq.push(np);
					}
				}
			}
		}
		qq.pop();
	}
	int ans = min(dist[end.y][end.x][H], dist[end.y][end.x][V]);
	if (ans >= INT_MAX-1)
		ans = -1;
	cout << ans << endl;
	return 0;
}
