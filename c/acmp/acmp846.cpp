/* ACMP 846 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

struct P {
	int x, y;
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<string> map(n);
	for (auto &r:map)
		cin >> r;
	P q;
	cin >> q.y >> q.x;
	q.x--, q.y--;
	int l;
	cin >> l;
	struct M {
		P p;
		int c;
	} mm[4];
	for (int i=0; i<4; i++) {
		cin >> mm[i].p.y >> mm[i].p.x >> mm[i].c;
		mm[i].p.x--; mm[i].p.y--;
	}
	vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
	queue<P> qq;
	if (map[q.y][q.x] == '0') {
		qq.push(q);
		dist[q.y][q.x] = 0;
	}
	while (!qq.empty()) {
		const P &p = qq.front();
		for (const P &m:moves) {
			const P np = P {p.x+m.x, p.y+m.y};
			if (map[np.y][np.x] == '0' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
				dist[np.y][np.x] = dist[p.y][p.x]+1;
				qq.push(np);
			}
		}
		qq.pop();
	}
#if 0
	for (auto &r:dist) {
		for (auto &d:r)
			if (d < INT_MAX)
				cerr << setw(2) << d;
			else
				cerr << setw(2) << ' ';
		cerr << endl;
	}
#endif
	int ans = 0;
	for (int i=0; i<4; i++) {
		if (dist[mm[i].p.y][mm[i].p.x] <= l)
			ans += mm[i].c;
	}
	cout << ans << endl;
	return 0;
}
