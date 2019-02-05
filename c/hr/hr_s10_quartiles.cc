#include <cstdio>
#include <cinttypes>
#include <algorithm>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-quartiles */
using namespace std;

// median with 1 dec digit
int get_median10(const int *srt, int b, int e) {
	int median10;
	int l = e-b;
	int m = b+l/2;
	if (l & 1)
		median10 = srt[m]*10;
	else
		median10 = (((srt[m-1]+srt[m])*10+1)/2);
	return median10;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	uint64_t sm = 0;
	int aa[n];
	for (int i=0; i<n; i++) {
		scanf("%d", &aa[i]);
		sm += aa[i];
	}
	sort(aa, aa+n);
	int q1 = get_median10(aa, 0, n/2);
	int q2 = get_median10(aa, 0, n);
	int q3 = get_median10(aa, n/2+(n&1), n);
	printf("%d\n%d\n%d\n", q1/10, q2/10, q3/10);
	return 0;
}
