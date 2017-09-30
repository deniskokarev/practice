/* ACMP 518 */
#include <stdio.h>
#include <inttypes.h>
#include <vector>

using namespace std;

struct C {
	bool free;
	uint64_t cnt[31]; // k->cnt
	operator bool() const {
		return free;
	}
	C():cnt{0} {}
};

int main(int argc, char **argv) {
	int n, k, m;
	fscanf(stdin, "%d%d", &n, &k);
	vector<vector<vector<C>>> mm(2, vector<vector<C>>(n+2, vector<C>(32)));
	fgetc(stdin);
	for (int r=1; r<=n; r++) {
		int c;
		m = 1;
		while ((c=fgetc(stdin)) != '\n' && (c>=0) && m<32)
			mm[0][r][m++].free = (c=='0');
	}
	m--;
	mm[0][1][1].cnt[0] = 1;
	for (int ki=1; ki<=k; ki++) {
		int curr = ki&1;
		int prev = (ki+1)&1;
		for (int r=1; r<=n; r++) {
			for (int c=1; c<=m; c++) {
				mm[curr][r][c].free = mm[prev][r][c].free;
				fill(mm[curr][r][c].cnt, mm[curr][r][c].cnt+31, 0);
			}
		}
		for (int r=1; r<=n; r++) {
			for (int c=1; c<=m; c++) {
				if (mm[prev][r][c]) {
					for (int kj=0; kj<k; kj++) {
						mm[curr][r-1][c].cnt[kj+1] += mm[prev][r][c].cnt[kj];
						mm[curr][r+1][c].cnt[kj+1] += mm[prev][r][c].cnt[kj];
						mm[curr][r][c-1].cnt[kj+1] += mm[prev][r][c].cnt[kj];
						mm[curr][r][c+1].cnt[kj+1] += mm[prev][r][c].cnt[kj];
					}
				}
			}
		}
	}
	printf("%lld\n", mm[k&1][n][m].cnt[k]);
	return 0;
}
