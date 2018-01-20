/* ACMP 99 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct P {
	int x, y, z;
};

const P moves[] = {{1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, 1}}; 

int main(int argc, char **argv) {
	int h, m, n;
	cin >> h >> m >> n;
	vector<vector<string>> map(h+2, vector<string>(m+2, string(n+2, 'o')));
	P start {1, 1, 1}, finish {h, m, n};
	for (int i=1; i<=h; i++) {
		for (int j=1; j<=m; j++) {
			string s;
			cin >> s;
			for (int k=1; k<=n && k-1<s.length(); k++) {
				map[i][j][k] = s[k-1];
				if (s[k-1] == '1')
					start = P {k, j, i};
				else if (s[k-1] == '2')
					finish = P {k, j, i};
			}
		}
	}
	map[start.z][start.y][start.x] = '.';
	map[finish.z][finish.y][finish.x] = '.';
	vector<vector<vector<int>>> dist(h+2, vector<vector<int>>(m+2, vector<int>(n+2, INT_MAX-1)));
	dist[start.z][start.y][start.x] = 0;
	queue<P> qq;
	qq.push(start);
	while (qq.size() > 0) {
		const P &p = qq.front();
		if (map[p.z][p.y][p.x] != 'o') {
			for (auto &m:moves) {
				const P &np = P {p.x+m.x, p.y+m.y, p.z+m.z};
				if (dist[np.z][np.y][np.x] > dist[p.z][p.y][p.x]+1) {
					dist[np.z][np.y][np.x] = dist[p.z][p.y][p.x]+1;
					qq.push(np);
				}
			}
		}
		qq.pop();
	}
	cout << dist[finish.z][finish.y][finish.x]*5 << endl;
	return 0;
}
