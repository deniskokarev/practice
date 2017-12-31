/* ACMP 1186 */
#include <cstdio>
#include <cstring>
#include <cmath>

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int pad = (1<<l2)-1;
	long long aa[pad+(1<<l2)];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++)
		scanf("%lld", &aa[pad+i]);
	for (int i=dim(aa)-1; i>=0; i-=2)
		aa[(i-1)/2] = aa[i]+aa[i-1];
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		char cmd[32];
		int arg1, arg2;
		scanf("%31s%d%d", cmd, &arg1, &arg2);
		if (cmd[0] == 's') {
			int l = pad + arg1 - 1;
			int r = pad + arg2 - 1;
			long long suml = 0, sumr = 0;
			while (l<r) {
				if ((l&1) == 0)
					suml += aa[l];
				l = l/2;
				if ((r&1) == 1)
					sumr += aa[r];
				r = r/2-1;
			}
			if (l == r)
				suml += aa[l];
			printf("%lld ", suml + sumr);
		} else if (cmd[0] == 'u') {
			int p = pad + arg1 - 1;
			long long nv = arg2;
			long long d = nv-aa[p];
			for (; p>0; p=(p-1)/2)
				aa[p] += d;
		}
	}
	printf("\n");
	return 0;
}
