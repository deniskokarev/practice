/* ACMP 1389 */
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>

using namespace std;

struct P {
	int i, j;
	P operator+(const P &b) {
		return P {i+b.i, j+b.j};
	}
	P operator-(const P &b) {
		return P {i-b.i, j-b.j};
	}
};

struct M {
	P delta;
	unsigned cost;
	operator bool() const {
		return delta.i != 0 || delta.j != 0;
	}
};

const M moves[] = {{{1,0},1},{{-1,0},1},{{0,1},2},{{0,-1},2}};

struct Q {
	M from;
	P to;
	unsigned cost;
	bool operator<(const Q &b) const {
		return cost > b.cost;
	}
};

struct E {
	M m;
	E *next;
};

struct D {
	M from;
	bool seen;
	bool prn;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E *bb[n+2][m+2];
	memset(bb, 0, sizeof(bb));
	E allee[n*m*4], *e=allee;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			int code;
			scanf("%d", &code);
			if (code & 1) {
				*e = E {M {{1, 0}, 0}, bb[i][j]};
				bb[i][j] = e++;
				*e = E {M {{-1, 0}, 0}, bb[i+1][j]};
				bb[i+1][j] = e++;
			}
			if (code & 2) {
				*e = E {M {{0, 1}, 0}, bb[i][j]};
				bb[i][j] = e++;
				*e = E {M {{0, -1}, 0}, bb[i][j+1]};
				bb[i][j+1] = e++;
			}
		}
	}
	D dist[n+2][m+2];
	for (int i=0; i<n+2; i++)
		for (int j=0; j<m+2; j++)
			dist[i][j] = D {M{{-1,-1},0}, false, false};
	for (int i=0; i<n+2; i++)
		dist[i][0].seen = dist[i][m+1].seen = true;
	for (int j=0; j<m+2; j++)
		dist[0][j].seen = dist[n+1][j].seen = true;
	priority_queue<Q> qq;
	qq.push(Q{M{{0,0},0},P{1,1},0});
	int cnt = 0;
	unsigned sum = 0;
	// almost standard MST
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (!dist[top.to.i][top.to.j].seen) {
			cnt += (top.cost != 0);
			sum += top.cost;
			dist[top.to.i][top.to.j].seen = true;
			dist[top.to.i][top.to.j].from = top.from;
			for (const E *e = bb[top.to.i][top.to.j]; e; e=e->next)
				qq.push(Q{e->m, top.to+e->m.delta, 0});
			for (const M &m:moves)
				qq.push(Q{m, top.to+m.delta, m.cost});
		}
	}
	// it's only tricky to print results
	printf("%d %d\n", cnt, sum);
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			if (!dist[i][j].prn) {
				P p1 {i,j};
				P p2;
				M m = dist[p1.i][p1.j].from;
				while (m) {
					p2 = p1;
					p1 = p1 - m.delta;
					if (m.cost) {
						//	fprintf(stderr, "[%d,%d] <-> [%d,%d] (%d)\n", p1.i, p1.j, p2.i, p2.j, m.cost);
						if (p1.i < p2.i || p1.j < p2.j)
							printf("%d %d %d\n", p1.i, p1.j, m.cost);
						else
							printf("%d %d %d\n", p2.i, p2.j, m.cost);
					}
					dist[p2.i][p2.j].prn = true;
					if (dist[p1.i][p1.j].prn)
						break;
					dist[p1.i][p1.j].prn = true;
					m = dist[p1.i][p1.j].from;
				}
			}
		}
	}
	return 0;
}
