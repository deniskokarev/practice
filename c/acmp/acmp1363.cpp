/* ACMP 1363 */
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

struct P {
	int x, y;
	int dist;
	P operator+(const P &b) const {
		return P {x+b.x, y+b.y, dist+1};
	}
	bool valid(const P &border) const {
		return x>=0 && x<border.x && y>=0 && y<border.y;
	}
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<string> map(n);
	vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
	P treasure;
	const P border = P {m, n, -1};
	for (int i=0; i<n; i++) {
		cin >> map[i];
		const string &s = map[i];
		assert(s.size() == m);
		for (int j=0; j<m; j++)
			if (s[j] == '*')
				treasure = P {j, i, 0};
	}
	map[treasure.y][treasure.x] = '0';
	queue<P> qq;
	qq.push(treasure);
	while (qq.size() > 0) {
		const P &p = qq.front();
		if (p.valid(border) && map[p.y][p.x] == '0' && dist[p.y][p.x] > p.dist) {
			dist[p.y][p.x] = p.dist;
			for (auto &m:moves)
				qq.push(p+m);
		}
		qq.pop();
	}
	int k;
	cin >> k;
	int mni = -1;
	int mn = INT_MAX;
	for (int i=0; i<k; i++) {
		P p;
		cin >> p.y >> p.x;
		p.y--, p.x--;
		if (mn > dist[p.y][p.x]) {
			mni = i+1;
			mn = dist[p.y][p.x];
		}
	}
	cout << mni << endl;
	return 0;
}
