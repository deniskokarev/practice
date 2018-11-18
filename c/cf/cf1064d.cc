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

constexpr int INF = INT_MAX/2;

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
	int xx[n+2][m+2];
	int yy[n+2][m+2];
	for (int i=0; i<n+2; i++)
		for (int j=0; j<m+2; j++)
			if (bb[i][j] == '.')
				xx[i][j] = yy[i][j] = INF;
			else
				xx[i][j] = yy[i][j] = -INF;
	deque<Q> qq;
	qq.push_back(Q{s, 0, 0});
	xx[s.r][s.c] = 0;
	while (!qq.empty()) {
		Q t = qq.front();
		qq.pop_front();
		if (t.x < xx[t.p.r+1][t.p.c]) {
			xx[t.p.r+1][t.p.c] = t.x;
			qq.push_front(Q {P {t.p.r+1, t.p.c}, t.x, t.y});
		}
		if (t.x < xx[t.p.r-1][t.p.c]) {
			xx[t.p.r-1][t.p.c] = t.x;
			qq.push_front(Q {P {t.p.r-1, t.p.c}, t.x, t.y});
		}
		if (t.x < xx[t.p.r][t.p.c+1]) {
			xx[t.p.r][t.p.c+1] = t.x;
			qq.push_front(Q {P {t.p.r, t.p.c+1}, t.x, t.y});
		}
		if (t.x < x && t.x+1 < xx[t.p.r][t.p.c-1]) {
			xx[t.p.r][t.p.c-1] = t.x+1;
			qq.push_back(Q {P {t.p.r, t.p.c-1}, t.x+1, t.y});
		}
	}
	qq.push_back(Q{s, 0, 0});
	yy[s.r][s.c] = 0;
	while (!qq.empty()) {
		Q t = qq.front();
		qq.pop_front();
		if (t.y < yy[t.p.r+1][t.p.c]) {
			yy[t.p.r+1][t.p.c] = t.y;
			qq.push_front(Q {P {t.p.r+1, t.p.c}, t.x, t.y});
		}
		if (t.y < yy[t.p.r-1][t.p.c]) {
			yy[t.p.r-1][t.p.c] = t.y;
			qq.push_front(Q {P {t.p.r-1, t.p.c}, t.x, t.y});
		}
		if (t.y < y && t.y+1 < yy[t.p.r][t.p.c+1]) {
			yy[t.p.r][t.p.c+1] = t.y+1;
			qq.push_back(Q {P {t.p.r, t.p.c+1}, t.x, t.y+1});
		}
		if (t.y < yy[t.p.r][t.p.c-1]) {
			yy[t.p.r][t.p.c-1] = t.y;
			qq.push_front(Q {P {t.p.r, t.p.c-1}, t.x, t.y});
		}
	}
	int ans = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			ans += (xx[i][j] > -INF && xx[i][j] < INF && yy[i][j] > -INF && yy[i][j] < INF);
	printf("%d\n", ans);
	return 0;
}
