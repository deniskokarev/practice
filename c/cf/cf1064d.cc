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

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	P s;
	scanf("%d%d", &s.r, &s.c);
	int x, y;
	scanf("%d%d", &x, &y);
	char bbx[n+2][m+2];
	memset(bbx, '*', sizeof(bbx));
	for (int i=1; i<=n; i++) {
		scanf("%s", bbx[i]+1);
		bbx[i][m+1] = '*';
	}
	char bby[n+2][m+2];
	memcpy(bby, bbx, sizeof(bbx));
	Q bb[n+2][m+2];
	memset(bb, 0, sizeof(bb));
	queue<P> qq;
	qq.push(s);
	bbx[s.r][s.c] = '+';
	while (!qq.empty()) {
		P p = qq.front();
		qq.pop();
		if (bbx[p.r+1][p.c] == '.') {
			bbx[p.r+1][p.c] = '+';
			bb[p.r+1][p.c] = bb[p.r][p.c];
			qq.push(P {p.r+1, p.c});
		}
		if (bbx[p.r-1][p.c] == '.') {
			bbx[p.r-1][p.c] = '+';
			bb[p.r-1][p.c] = bb[p.r][p.c];
			qq.push(P {p.r-1, p.c});
		}
		if (bb[p.r][p.c].x < x && bbx[p.r][p.c-1] == '.') {
			bbx[p.r][p.c-1] = '+';
			bb[p.r][p.c-1] = bb[p.r][p.c];
			bb[p.r][p.c-1].x++;
			qq.push(P {p.r, p.c-1});
		}
		if (bbx[p.r][p.c+1] == '.') {
			bbx[p.r][p.c+1] = '+';
			bb[p.r][p.c+1] = bb[p.r][p.c];
			bb[p.r][p.c+1].y++;
			qq.push(P {p.r, p.c+1});
		}
	}
	memset(bb, 0, sizeof(bb));
	qq.push(s);
	bby[s.r][s.c] = '+';
	while (!qq.empty()) {
		P p = qq.front();
		qq.pop();
		if (bby[p.r+1][p.c] == '.') {
			bby[p.r+1][p.c] = '+';
			bb[p.r+1][p.c] = bb[p.r][p.c];
			qq.push(P {p.r+1, p.c});
		}
		if (bby[p.r-1][p.c] == '.') {
			bby[p.r-1][p.c] = '+';
			bb[p.r-1][p.c] = bb[p.r][p.c];
			qq.push(P {p.r-1, p.c});
		}
		if (bby[p.r][p.c-1] == '.') {
			bby[p.r][p.c-1] = '+';
			bb[p.r][p.c-1] = bb[p.r][p.c];
			bb[p.r][p.c-1].x++;
			qq.push(P {p.r, p.c-1});
		}
		if (bb[p.r][p.c].y < y && bby[p.r][p.c+1] == '.') {
			bby[p.r][p.c+1] = '+';
			bb[p.r][p.c+1] = bb[p.r][p.c];
			bb[p.r][p.c+1].y++;
			qq.push(P {p.r, p.c+1});
		}
	}
	int ans = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			ans += (bbx[i][j] == '+' && bby[i][j] == '+');
	printf("%d\n", ans);
	return 0;
}
