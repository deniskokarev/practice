/* ACMP 690 */
#include <algorithm>
#include <random>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>

struct P {
	int8_t x, y;
};

inline P operator+(const P a, const P b) {
	return P {(int8_t)(a.x+b.x), (int8_t)(a.y+b.y)};
}

struct SP {
	int score;
	P p;
};

inline bool operator<(const SP &a, const SP &b) {
	return a.score < b.score;
}

constexpr int MSZ = 104; // with +2 padding on each side

static const P kmoves[8] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

// gradient from each x,y
struct GRAD {
	int sz;
	SP moves[8];
};

// caclulate Warnsdorf's score for each square
static void calc_potential(const char brd[MSZ][MSZ], int potential[MSZ][MSZ], int n, int m, int depth) {
	int pptn[2][MSZ][MSZ];
	memset(pptn, 0, sizeof(pptn));
	for (int r=2; r<n+2; r++)
		for (int c=2; c<m+2; c++)
			if (brd[r][c] == '.')
				pptn[0][r][c] = 1;
	for (int i=1; i<depth; i++) {
		auto &ptn = pptn[i&1];
		auto &optn = pptn[(i+1)&1];
		for (int8_t r=2; r<n+2; r++) {
			for (int8_t c=2; c<m+2; c++) {
				if (brd[r][c] == '.') {
					P p = {c, r};
					for (auto &km:kmoves) {
						P nm = p+km;
						if (brd[nm.y][nm.x] == '.')
							ptn[nm.y][nm.x] += optn[p.y][p.x];
					}
				}
			}
		}
	}
	memcpy(potential, pptn[(depth+1)&1], sizeof(pptn[0]));
}

// calculate the most favorable move from each square
static void calc_gradient(const char brd[MSZ][MSZ], const int potential[MSZ][MSZ], GRAD grad[MSZ][MSZ], int n, int m) {
	// there must be a deliberate test for our approach, try to jump over it using random shuffle
	std::mt19937 rnd(2);
	for (int8_t i=2; i<n+2; i++) {
		for (int8_t j=2; j<m+2; j++) {
			P p = {j, i};
			int sz = 0;
			auto &g = grad[i][j];
			if (brd[i][j] == '.') {
				for (auto &km:kmoves) {
					P nm = p+km;
					auto score = potential[nm.y][nm.x];
					if (score > 0)
						g.moves[sz++] = {score, nm};
				}
				std::sort(g.moves, g.moves+sz);
				// introduce random shuffle
				int shufsz;
				for (shufsz=1; shufsz<sz && g.moves[shufsz-1].score == g.moves[shufsz].score; shufsz++);
				std::random_shuffle(g.moves, g.moves+shufsz, [&rnd](int ln){return rnd()%ln;});
			}
			g.sz = sz;
		}
	}
}

static bool dfs(char brd[MSZ][MSZ], const GRAD grad[MSZ][MSZ], const P p, int sqcnt, int solution[MSZ][MSZ], int &missed) {
	if (brd[p.y][p.x] == '.') {
		if (sqcnt == 1) {
			solution[p.y][p.x] = 1;
			return true;
		} else {
			auto &g = grad[p.y][p.x];
			brd[p.y][p.x] = 'K';
			for (int i=0; i<g.sz; i++) {
				if (dfs(brd, grad, g.moves[i].p, sqcnt-1, solution, missed)) {
					solution[p.y][p.x] = sqcnt;
					return true;
				}
			}
			brd[p.y][p.x] = '.';
			missed++;
			return false;
		}
	} else {
		return false;
	}
}

int main(int argc, char **argv) {
	int missed = 0;
	char brd[MSZ][MSZ];
	int potential[MSZ][MSZ];
	int solution[MSZ][MSZ];
	GRAD grad[MSZ][MSZ];
	int n, m;
	scanf("%d%d", &n, &m);
	assert(n <= MSZ-4 && m <= MSZ-4);
	memset(brd, 'X', sizeof(brd));
	P kp;
	int sqcnt = 0;
	for (int8_t i=0; i<n; i++) {
		int8_t r = i+2;
		char s[1024];;
		scanf("%1023s", s);
		for (int8_t j=0,c=2; c<m+2 && s[j]; c++,j++) {
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
	calc_potential(brd, potential, n, m, 2);
	calc_gradient(brd, potential, grad, n, m);
#if 0
	for (int i=0; i<n+4; i++) {
		for (int j=0; j<m+4; j++)
			fprintf(stderr, "%6d ", potential[i][j]);
		fprintf(stderr, "\n");
	}
#endif
	if (dfs(brd, grad, kp, sqcnt, solution, missed)) {
		for (int r=2; r<n+2; r++) {
			for (int c=2; c<m+2; c++)
				printf("%3d ", (solution[r][c]>0)?sqcnt-solution[r][c]+1:0);
			printf("\n");
		}
	} else {
		assert(false && "Hey, they've told there is a solution");
	}
#if 1
	fprintf(stderr, "missed: %d\n", missed);
#endif
	return 0;
}
