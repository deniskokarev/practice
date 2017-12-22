/* ACMP 1179 */
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define max(A,B) ((A>B)?A:B)
#define min(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	int _n, _k;
	scanf("%d%d", &_n, &_k);
	const int n = _n;
	const int k = _k;
	const int len = max(sqrt(n), 1);
	const int nb = (n+len-1)/len;
	int bucket[nb];
	int aa[n];
	{
		for (auto &b:bucket)
			b = INT_MAX;
		int bi, i;
		for (bi=0,i=0; bi<n/len; bi++) {
			for (int j=0; j<len; j++,i++) {
				scanf("%d", &aa[i]);
				bucket[bi] = min(bucket[bi], aa[i]);
			}
		}
		for (;i<n;i++) {
			scanf("%d", &aa[i]);
			bucket[bi] = min(bucket[bi], aa[i]);
		}
	}
	for (int l=0; l<=n-k; l++) {
		const int r = l+k-1;
		const int lb = l/len;
		const int rb = r/len;
		int mn = INT_MAX;
		if (rb-lb > 1) {
			for (int bi=lb+1; bi<rb; bi++)
				mn = min(mn, bucket[bi]);
			int l_hi = (lb+1)*len;
			for (int i=l; i<l_hi; i++)
				mn = min(mn, aa[i]);
			int r_lo = rb*len;
			for (int i=r_lo; i<=r; i++)
				mn = min(mn, aa[i]);
		} else {
			for (int i=l; i<=r; i++)
				mn = min(mn, aa[i]);
		}
		printf("%d ", mn);
	}
	printf("\n");
	return 0;
}
