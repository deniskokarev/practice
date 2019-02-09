#include <cstdio>
#include <cinttypes>
#include <vector>
/* CodeForces CF1107D problem */
using namespace std;

static const int hex[16][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 0, 1, 1},
	{0, 1, 0, 0},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{0, 1, 1, 1},
	{1, 0, 0, 0},
	{1, 0, 0, 1},
	{1, 0, 1, 0},
	{1, 0, 1, 1},
	{1, 1, 0, 0},
	{1, 1, 0, 1},
	{1, 1, 1, 0},
	{1, 1, 1, 1}
};

int prime_factors(uint64_t n, uint64_t p[]) {
	int np = 0;
	for (uint64_t i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

static int cnt(const vector<vector<int>> &mm, int i, int j, int x) {
	return mm[(i+1)*x][(j+1)*x] + mm[i*x][j*x] - mm[(i+1)*x][j*x] - mm[i*x][(j+1)*x];
}

bool can_compact(const vector<vector<int>> &mm, const int n, const int x) {
	for (int i=0; i<n/x; i++) {
		for (int j=0; j<n/x; j++) {
			int sm = cnt(mm, i, j, x);
			if (sm != x*x && sm != 0)
				return false;
		}
	}
	return true;
}

static void dbg_prn(const vector<vector<int>> &mm, int n) {
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			fprintf(stderr, "%d ", cnt(mm, i, j, 1));
		fprintf(stderr, "\n");
	}
}

int main(int argc, char **argv) {
	char s[10000];
	int n;
	fscanf(stdin, "%d", &n);
	(void)fgets(s, sizeof(s), stdin);
	vector<vector<int>> mm(n+2, vector<int>(n+2));
	int r = 0;
	while (fgets(s, sizeof(s), stdin) >= 0 && r < n) {
		for (int i=0; i<n/4; i++)
			for (int j=0; j<4; j++)
				if (s[i] >= '0' && s[i] <= '9')
					mm[r+1][i*4+j+1] = hex[s[i]-'0'][j];
				else
					mm[r+1][i*4+j+1] = hex[10+s[i]-'A'][j];
		r++;
	}
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			mm[i][j] += mm[i-1][j] + mm[i][j-1] - mm[i-1][j-1];
	//dbg_prn(mm, n);
	uint64_t pf[64];
	int pf_sz = prime_factors(n, pf);
	int x = 1;
	for (int i=0; i<pf_sz; i++)
		if (can_compact(mm, n, x*pf[i]))
			x *= pf[i];
	printf("%d\n", x);
	return 0;
}
