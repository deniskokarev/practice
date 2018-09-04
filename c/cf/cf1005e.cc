#include <stdio.h>
#include <string.h>
#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <inttypes.h>
/* CodeForces CF1005E problem */

/**
 * Plain C-style Fenwick implementation
 */
static void fw_init(int64_t *fw, int sz) {
	memset(fw, 0, sizeof(fw[0])*sz);
}

static void fw_upd(int64_t *fw, int p, int inc, int sz) {
	for (int i=p; i<sz; i|=i+1)
		fw[i] += inc;
}

static int64_t fw_sum(int64_t *fw, int p, int sz) {
	int64_t sum = 0;
	for (int i=p; i>=0; i=(i&(i+1))-1)
		sum += fw[i];
	return sum;
}

int64_t cnt(int *aa, int n, int m) {
	int64_t c = 0;
	int s_ofs = n+1;	// 2 make diff pos
	int fw_sz = 2*n+2;
	int64_t fw[fw_sz];
	fw_init(fw, fw_sz);
	int ge[n+1];
	int lt[n+1];
	ge[0] = lt[0] = 0;
	for (int i=1; i<=n; i++) {
		lt[i] = lt[i-1]+(aa[i]<m);
		ge[i] = ge[i-1]+(aa[i]>=m);
	}
	for (int i=0; i<=n; i++) {
		int diff = ge[i]-lt[i];
		diff += s_ofs;
		c += fw_sum(fw, diff-1, fw_sz);
		fw_upd(fw, diff, +1, fw_sz);
	}
	return c;
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int aa[n+1];
	for (int i=1; i<=n; i++)
		scanf("%d", aa+i);
	printf("%" PRId64 "\n", cnt(aa, n, m)-cnt(aa, n, m+1));
	return 0;
}
