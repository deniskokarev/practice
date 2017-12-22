/* ACMP 1182 */
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define max(A,B) ((A>B)?A:B)
#define min(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);
	const int len = max(sqrt(n), 1);
	const int nb = (n+len-1)/len;
	int bucket[nb];
	int aa[n];
	for (auto &b:bucket)
		b = 0;
	for (auto &a:aa)
		a = 0;
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		const int lb = l/len;
		const int rb = r/len;
		int mx = 0;
		if (rb-lb > 1) {
			for (int bi=lb+1; bi<rb; bi++)
				mx = max(mx, bucket[bi]);
			int l_hi = (lb+1)*len;
			for (int i=l; i<l_hi; i++)
				mx = max(mx, aa[i]);
			int r_lo = rb*len;
			for (int i=r_lo; i<=r; i++)
				mx = max(mx, aa[i]);
		} else {
			for (int i=l; i<=r; i++)
				mx = max(mx, aa[i]);
		}
		if (mx < k) {
			printf("Yes\n");
			for (int bi=lb; bi<=rb; bi++)
				bucket[bi]++;
			if (rb-lb > 1) {
				int l_hi = (lb+1)*len;
				for (int i=l; i<l_hi; i++)
					aa[i]++;
				int r_lo = rb*len;
				for (int i=r_lo; i<=r; i++)
					aa[i]++;
			} else {
				for (int i=l; i<=r; i++)
					aa[i]++;
			}
		} else {
			printf("No\n");
		}
	}
	return 0;
}
