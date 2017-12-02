/* ACMP 17 */
#include <stdio.h>
#include <inttypes.h>
#include <limits.h>

constexpr int MX_SZ = 1024*32;

#define MIN(A,B) ((A<B)?A:B)
#define MAX(A,B) ((A>B)?A:B)

int main(int argc, char **argv) {
	int s[MX_SZ];
	int sz = 0;
	int n;
	fscanf(stdin, "%d", &n);
	while (sz < n && sz < MX_SZ && !feof(stdin) && (fscanf(stdin, "%d", &s[sz]) == 1))
		sz++;
	int zz[sz]; // suffix fn z function // taken from e-maxx
	zz[0] = 0;
	for (int i=1,l=0,r=0; i<sz; i++) {
		if (i <= r)
			zz[i] = MIN(r-i+1, zz[i-l]);
		int cnt;
		for (cnt=0; i+cnt < sz && s[cnt] == s[i+cnt]; cnt++);
		zz[i] = cnt;
		if (i+cnt-1 > r) {
			l = i;
			r = i+cnt-1;
		}
	}
#if 0
	for (auto &z:zz)
		fprintf(stderr, "%d ", z);
	fprintf(stderr, "\n");
#endif
	int ans = sz-1;
	for (int i=2; i<sz; i++) {
		if (zz[sz-i] == i) {
			ans = i-1;
			break;
		}
	}
	printf("%d\n", ans);
    return 0;
}
