#include <cstdio>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/kindergarten-adventures/problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int hh[3*n];
	for (int i=0; i<n; i++) {
		scanf("%d", &hh[i+n]);
		hh[i+2*n] = hh[i+n];
	}
	int64_t aa[3*n];
	fill(aa, aa+3*n, 0);
	for (int i=n; i<3*n; i++) {
		int bi = i - n + 1;
		int ei = i - hh[i] + 1;
		if (bi < ei)
			aa[bi]++, aa[ei]--;
	}
	for (int i=1; i<3*n; i++)
		aa[i] += aa[i-1];
	int mxi = int(max_element(aa+n, aa+3*n) - aa);
	printf("%d\n", mxi % n + 1);
	return 0;
}
