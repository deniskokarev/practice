#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
/* CodeForces CF1064D problem */
using namespace std;

struct P {
	int r, c;
};

struct Q {
	P p;
	int x, y;
};

struct QCMP {
	int x, y;
	bool operator()(const Q &a, const Q &b) {
		return min(x-a.x, y-a.y) > min(x-b.x, y-b.y);
	}
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	P s;
	scanf("%d%d", &s.r, &s.c);
	int x, y;
	scanf("%d%d", &x, &y);
	char bb[n+2][m+2];
	memset(bb, '*', sizeof(bb));
	for (int i=1; i<=n; i++) {
		scanf("%s", bb[i]+1);
		bb[i][m+1] = '*';
	}
	priority_queue<Q, std::vector<Q>, QCMP> qq(QCMP {x, y});
	qq.push(Q{s, 0, 0});
	bb[s.r][s.c] = 'X';
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (bb[top.p.r+1][top.p.c] == '.') {
			bb[top.p.r+1][top.p.c] = 'X';
			qq.push(Q { P {top.p.r+1, top.p.c}, top.x, top.y});
		}
		if (bb[top.p.r-1][top.p.c] == '.') {
			bb[top.p.r-1][top.p.c] = 'X';
			qq.push(Q { P {top.p.r-1, top.p.c}, top.x, top.y});
		}
		if (top.y < y && bb[top.p.r][top.p.c+1] == '.') {
			bb[top.p.r][top.p.c+1] = 'X';
			qq.push(Q { P {top.p.r, top.p.c+1}, top.x, top.y+1});
		}
		if (top.x < x && bb[top.p.r][top.p.c-1] == '.') {
			bb[top.p.r][top.p.c-1] = 'X';
			qq.push(Q { P {top.p.r, top.p.c-1}, top.x+1, top.y});
		}
	}
	int ans = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			ans += (bb[i][j] == 'X');
	printf("%d\n", ans);
	return 0;
}
