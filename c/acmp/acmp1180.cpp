/* ACMP 1180 */
#include <stdio.h>
#include <math.h>
#include <memory.h>

#define max(A,B) ((A>B)?A:B)

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int b = max(sqrt(n), 1);
	int bucket[(n+b-1)/b];
	int aa[n];
	memset(bucket, -1, sizeof(bucket));
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++) {
		scanf("%d", &aa[i]);
		int bi=i/b;
		bucket[bi] = max(bucket[bi], aa[i]);
	}
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		int lb = l/b;
		int rb = r/b;
		int mx = -1;
		if (rb-lb > 1) {
			for (int bi=lb+1; bi<rb; bi++)
				mx = max(mx, bucket[bi]);
			int l_hi = (lb+1)*b;
			for (int i=l; i<l_hi; i++)
				mx = max(mx, aa[i]);
			int r_lo = rb*b;
			for (int i=r_lo; i<=r; i++)
				mx = max(mx, aa[i]);
		} else {
			for (int i=l; i<=r; i++)
				mx = max(mx, aa[i]);
		}
		printf("%d ", mx);
	}
	printf("\n");
	return 0;
}
