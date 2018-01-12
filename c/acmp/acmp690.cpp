/* ACMP 690 */
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <assert.h>

using namespace std;

struct P {
	int x, y;
	P operator+(const P &b) const {
		return P {x+b.x, y+b.y};
	}
};

static const P moves[] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

// to be used in Warnsdorf's empiric rule
int mvcnt(vector<vector<char>> &brd, const P &from, int depth) {
	if (brd[from.y][from.x] == '.') {
		if (depth == 0) {
			return 1;
		} else {
			int c = 1;
			brd[from.y][from.x] = 'K';
			for (auto &m:moves)
				c += mvcnt(brd, from+m, depth-1);
			brd[from.y][from.x] = '.';
			return c;
		}
	} else {
		return 0;
	}
}

bool dfs(vector<vector<char>> &brd, const P &p, vector<vector<int>> &log, int sqcnt) {
	if (sqcnt == 1) {
		if (brd[p.y][p.x] == '.') {
			log[p.y-2][p.x-2] = sqcnt;
			return true;
		} else {
			return false;
		}
	} else if (brd[p.y][p.x] == '.') {
		struct CP {
			int cnt;
			P p;
			bool operator<(const struct CP &b) const {
				return cnt < b.cnt;
			}
		} ord[8]; // we'll order moves using Warnsdorf rule
		int sz = 0;
		brd[p.y][p.x] = 'K';
		for (auto &m:moves) {
			int c = mvcnt(brd, p+m, 1);
			//if (c > 0)
				ord[sz++] = {c, p+m};
		}
		sort(ord, ord+sz);
		for (int i=0; i<sz; i++) {
			if (dfs(brd, ord[i].p, log, sqcnt-1)) {
				log[p.y-2][p.x-2] = sqcnt;
				return true;
			}
		}
		brd[p.y][p.x] = '.';
		return false;
	} else {
		return false;
	}
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<char>> brd(n+4, vector<char>(m+4, 'X'));
	P kp;
	int sqcnt = 0;
	for (int i=0; i<n; i++) {
		int r = i+2;
		char s[1024];;
		scanf("%1023s", s);
		for (int j=0,c=2; c<m+2 && s[j]; c++,j++) {
			brd[r][c] = s[j];
			if (s[j] == 'K') {
				kp = {c, r};
				brd[r][c] = '.';
				sqcnt++;
			} else if (s[j] == '.') {
				sqcnt++;
			}
		}
	}
	vector<vector<int>> log(n, vector<int>(m, sqcnt+1));
	if (dfs(brd, kp, log, sqcnt)) {
		for (auto &r:log) {
			for (auto &c:r)
				printf("%3d ", sqcnt-c+1);
			printf("\n");
		}
	} else {
		assert(false && "Hey, they've told there is a solution");
	}
	return 0;
}
