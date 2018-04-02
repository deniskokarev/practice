/* ACMP 443 */
#include <stdio.h>
#include <algorithm>

constexpr int MXLEN = 101;

inline int myhash(const char *s, int m, const int (&pp)[MXLEN][10]) {
	int h = 0;
	for (int i=0; *s; i++,s++)
		h += pp[i][*s-'0'];
	return h%m;
}

int main(int argc, char **argv) {
	int n, m, x;
	scanf("%d%d%d", &n, &m, &x);
	// precompute hash for every digit at each place to minimize % op at runtime
	int pp[MXLEN][10] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
	for (int i=1; i<MXLEN; i++) {
		pp[i][0] = 0;
		pp[i][1] = (pp[i-1][1]*x) % m;
		for (int d=2; d<10; d++)
			pp[i][d] = pp[i][1]*d%m;
	}
	int hh[m];
	std::fill(hh, hh+m, 0);
	for (int i=0; i<n; i++) {
		char s[MXLEN];
		scanf("%s", s);
		hh[myhash(s, m, pp)]++;
	}
	int a = 0;
	for (auto h:hh)
		a += h*(h-1)/2;
	printf("%d\n", a);
	return 0;
}
