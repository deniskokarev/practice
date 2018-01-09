/* ACMP 765 */
#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>> &brd, int x, int y, int fill);

int visit(vector<vector<int>> &brd, int x, int y, int fill) {
	int cnt = 0;
	if (brd[y][x] != 'W' && brd[y][x] != 'B' && brd[y][x] != fill) {
		cnt++;
		brd[y][x] = fill;
	} else if (brd[y][x] == 'B') {
		cnt += dfs(brd, x, y, fill);
	}
	return cnt;
}

int dfs(vector<vector<int>> &brd, int x, int y, int fill) {
	if (brd[y][x] != 'B')
		return 0;
	int cnt = 0;
	brd[y][x] = fill;
	cnt += visit(brd, x-1, y, fill);
	cnt += visit(brd, x+1, y, fill);
	cnt += visit(brd, x, y-1, fill);
	cnt += visit(brd, x, y+1, fill);
	return cnt;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<int>> brd(n+2, vector<int>(n+2, 'W'));
	for (int r=1; r<=n; r++) {
		string s;
		cin >> s;
		for (int c=1,j=0; c<=n && j<s.length(); c++,j++)
			brd[r][c] = s[j];
	}
	int ans = 0;
	int gr = 'W';
	for (int y=1; y<=n; y++) {
		for (int x=1; x<=n; x++) {
			if (brd[y][x] == 'B') {
				gr++;
				if (dfs(brd, x, y, gr) == 1)
					ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
