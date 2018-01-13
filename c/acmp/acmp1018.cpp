/* ACMP 1018 */
#include <iostream>
#include <vector>
#include <queue>

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

static const P hmoves[] = {{1,0},{1,1},{-1,1},{-1,0},{-1,-1},{1,-1}};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	P mxp = {m, n};
	P start;
	cin >> start.x >> start.y;
	start = start + P {-1, -1};
	vector<string> brd(n);
	for (int i=0; i<n; i++)
		cin >> brd[i];
	vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
	dist[start.y][start.x] = 0;
	queue<P> qq;
	qq.push(start);
	int ans = -1;
	while (qq.size() > 0 && ans < 0) {
		const P &p = qq.front();
		for (auto &hm:hmoves) {
			const P np = p+hm;
			if (!np.valid(mxp)) {
				ans = dist[p.y][p.x]+1;
				break;
			} else if (brd[np.y][np.x] != '0' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
				dist[np.y][np.x] = dist[p.y][p.x]+1;
				qq.push(np);
			}
		}
		qq.pop();
	}
	if (ans < 0)
		cout << "No solution" << endl;
	else
		cout << ans << endl;
	return 0;
}
