/* ACMP 1188 */
#include <cstdio>
#include <cstring>
#include <cmath>

#define dim(X) ((int)(sizeof(X)/sizeof(X[0])))

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int pad = (1<<l2)-1;
	long long aa[pad+(n+1)/2*2];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++)
		scanf("%lld", &aa[pad+i]);
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		char cmd[32];
		scanf("%31s", cmd);
		if (cmd[0] == 'a') {
			int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			l += pad - 1;
			r += pad - 1;
			while (l<r) {
				if ((l&1) == 0)
					aa[l] += d;
				l = l/2;
				if ((r&1) == 1)
					aa[r] += d;
				r = r/2-1;
			}
			if (l == r)
				aa[l] += d;
		} else if (cmd[0] == 'g') {
			int p;
			scanf("%d", &p);
			p += pad - 1;
			long long v;
			for (v=0; p>0; p=(p-1)/2)
				v += aa[p];
			v += aa[0];
			printf("%lld ", v);
		}
	}
	printf("\n");
	return 0;
}
