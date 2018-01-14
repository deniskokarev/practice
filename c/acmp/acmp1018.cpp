/* ACMP 1018 */
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

struct P {
	int x, y;
    P operator+(const P &b) const {
        return P {x+b.x, y+b.y};
    }
    bool valid(const P &mx) const {
        return x>=0 && x<mx.x && y>=0 && y<mx.y;
    }
};

static const P hmoves[2][6] = {
	{{1,0},{1,1},{0,1},{-1,0},{0,-1},{1,-1}}, // even lines
	{{1,0},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1}} // odd lines
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	P mxp = {m, n};
	P start;
	cin >> start.y >> start.x;
	start = start + P {-1, -1};
	vector<string> brd(n);
	for (int i=0; i<n; i++) {
		cin >> brd[i];
		assert(brd[i].size() == m);
	}
	vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
	dist[start.y][start.x] = 0;
	queue<P> qq;
	qq.push(start);
	int ans = -1;
	while (qq.size() > 0 && ans < 0) {
		const P p = qq.front();
		qq.pop();
		for (auto &hm:hmoves[p.y&1]) {
			const P np = p+hm;
			if (!np.valid(mxp)) {
				ans = dist[p.y][p.x]+1;
				break;
			} else if (brd[np.y][np.x] != '0' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
				dist[np.y][np.x] = dist[p.y][p.x]+1;
				qq.push(np);
			}
		}
	}
	if (ans < 0)
		cout << "No solution" << endl;
	else
		cout << ans << endl;
	return 0;
}
