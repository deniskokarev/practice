/* ACMP 1185 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>

#define dim(X) (sizeof(X)/sizeof(X[0]))
#define max(A,B) ((A>B)?A:B)

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int pad = (1<<l2)-1;
	int aa[pad+(1<<l2)];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++)
		scanf("%d", &aa[pad+i]);
	for (int i=pad+n; i<dim(aa); i++)
		aa[i] = INT_MIN;
	for (int i=dim(aa)-1; i>0; i-=2)
		aa[(i-1)/2] = max(aa[i], aa[i-1]);
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		char cmd[32];
		int arg1, arg2;
		scanf("%31s%d%d", cmd, &arg1, &arg2);
		if (cmd[0] == 'm') {
			int l = pad + arg1 - 1;
			int r = pad + arg2 - 1;
			int mxl = INT_MIN, mxr = INT_MIN;
			while (l<r) {
				if ((l&1) == 0)
					mxl = max(mxl, aa[l]);
				l = l/2;
				if ((r&1) == 1)
					mxr = max(mxr, aa[r]);
				r = r/2-1;
			}
			if (l == r)
				mxl = max(mxl, aa[l]);
			printf("%d ", max(mxl, mxr));
		} else if (cmd[0] == 'u') {
			int p = pad + arg1 - 1;
			int mx = arg2;
			aa[p] = mx;
			for (int r=(p-1)/2; p>0 && aa[r]<mx; p=r,r=(p-1)/2)
				aa[r] = mx;
		}
	}
	printf("\n");
	return 0;
}
