/* ACMP 1182 */
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <limits.h>

#define max(A,B) ((A>B)?A:B)
#define min(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);
	const int len = max(sqrt(n), 1);
	const int nb = (n+len-1)/len;
	int mxmxbt[nb]; // partial segment stats
	int mxmnbt[nb]; // whole segment stats
	int aa[n];
	memset(mxmxbt, 0, sizeof(mxmxbt));
	memset(mxmnbt, 0, sizeof(mxmnbt));
	memset(aa, 0, sizeof(aa));
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		const int lb = l/len;
		const int rb = r/len;
		int mx = 0;
		for (int bi=lb+1; bi<rb; bi++)
			mx = max(mx, mxmxbt[bi]);
		mx = max(mx, mxmnbt[lb]);
		mx = max(mx, mxmnbt[rb]);
		if (rb>lb) {
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
			for (int bi=lb+1; bi<rb; bi++) {
				mxmxbt[bi]++;
				mxmnbt[bi]++;
			}
			if (rb > lb) {
				mx = 0;
				int l_hi = (lb+1)*len;
				for (int i=l; i<l_hi; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				mxmxbt[lb] = max(mxmxbt[lb], mx+mxmnbt[lb]);
				mx = 0;
				int r_lo = rb*len;
				for (int i=r_lo; i<=r; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				mxmxbt[rb] = max(mxmxbt[rb], mx+mxmnbt[rb]);
			} else {
				mx = 0;
				for (int i=l; i<=r; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				mxmxbt[lb] = max(mxmxbt[lb], mx+mxmnbt[lb]);
			}
		} else {
			printf("No\n");
		}
	}
	return 0;
}
