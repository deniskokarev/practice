#include <iostream>
#include <vector>
/* ACMP 1303 */
using namespace std;

struct P {
	int x, y;
};

static const P mv[] {{+1,0}, {0,+1}, {-1,0}, {0,-1}}; 

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<vector<vector<int>>> dyn(2, vector<vector<int>>(n+2, vector<int>(n+2, INT_MIN)));
	vector<vector<int>> mm(n+2, vector<int>(n+2));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			cin >> mm[i][j];
	int lvl = 0;
	dyn[lvl][1][1] = mm[1][1];
	while (k--) {
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=n; j++) {
				int mx = INT_MIN;
				for (auto &m:mv)
					mx = max(mx, dyn[lvl][i+m.y][j+m.x]);
				dyn[lvl^1][i][j] = mx+mm[i][j];
			}
		}
		lvl ^= 1;
	}
	int mx = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			mx = max(mx, dyn[lvl^1][i][j]);
	cout << mx << endl;
	return 0;
}
