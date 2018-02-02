/* ACMP 1365 */
#include <stdio.h>

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct P {
	short int x, y;
};

// prioritized point
struct PP {
	unsigned dist;
	P p;
	bool operator<(const PP &b) const {
		return dist > b.dist; 	// for min-heap
	}
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	short int n, m;
	P start {0, 0}, end {0, 0};
	fscanf(stdin, "%hd%hd%hd%hd%hd%hd", &n, &m, &start.y, &start.x, &end.y, &end.x);
	(void)fgetc(stdin);
	vector<string> map(n+2, string(m+2, '#'));
	for (int i=1; i<=n; i++) {
		char buf[m];
		fread(buf, 1, m, stdin);
		for (int j=0; j<m; j++)
			map[i][j+1] = buf[j];
		(void)fgetc(stdin);
	}
	vector<vector<unsigned>> dist(n+2, vector<unsigned>(m+2, UINT_MAX));
	dist[start.y][start.x] = 0;
	priority_queue<PP> pqq;
    pqq.push(PP {0, start});
	while (pqq.size() > 0) {
		const P p = pqq.top().p;
		pqq.pop();
		const unsigned d = dist[p.y][p.x];
		for (const auto &m:moves) {
			const P np = P {(short int)(p.x+m.x), (short int)(p.y+m.y)};
			const char mapv = map[np.y][np.x];
			unsigned &nd = dist[np.y][np.x]; // can safely use &
			if (mapv == '.' && nd > d+1) {
				nd = d+1;
				pqq.push(PP {d+1, np});
			} else if (mapv == 'W' && nd > d+2) {
				nd = d+2;
				pqq.push(PP {d+2, np});
			}
		}
	}
	int ans = (int)dist[end.y][end.x];
	printf("%d\n", ans);
	return 0;
}
