/* ACMP 128 */
#include <stdio.h>
#include <string.h>

struct P {
	int x, y;
    P operator+(const P &b) const {
        return P {x+b.x, y+b.y};
    }
    bool operator==(const P &b) const {
        return x == b.x && y == b.y;
    }
};

static const P kmoves[] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

int main(int argc, char **argv) {
	int n;
	P fr, to;
	scanf("%d%d%d%d%d", &n, &fr.x, &fr.y, &to.x, &to.y);
	fr = fr + P {1,1};
	to = to + P {1,1};
	char seen[n+4][n+4];
	memset(seen, 1, sizeof(seen));
	for (int i=2; i<n+2; i++)
		for (int j=2; j<n+2; j++)
			seen[i][j] = 0;
	struct {
		P sq;
		int len;
	} qq[n*n];
	int qh = 0;
	int qt = 0;
	qq[qt++] = {fr, 0};
	seen[fr.y][fr.x] = 1;
	int ans = (fr==to)?0:-1;
	while (qh < qt && ans < 0) {
		auto nxt = qq[qh++];
		for (auto km:kmoves) {
			P nsq = nxt.sq+km;
			if (nsq == to) {
				ans = nxt.len+1;
				break;
			} else if (seen[nsq.y][nsq.x] == 0) {
				qq[qt++] = {nsq, nxt.len+1};
				seen[nsq.y][nsq.x] = 1;
			}
		}
		qh %= n;
		qt %= n;
	}
	printf("%d\n", ans);
	return 0;
}
