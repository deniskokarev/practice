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
	int pbucket[nb]; // partial segment stats
	int wbucket[nb]; // whole segment stats
	int aa[n];
	memset(pbucket, 0, sizeof(pbucket));
	memset(wbucket, 0, sizeof(wbucket));
	memset(aa, 0, sizeof(aa));
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		const int lb = l/len;
		const int rb = r/len;
		int mx = 0;
		for (int bi=lb+1; bi<rb; bi++)
			mx = max(mx, pbucket[bi]);
		mx = max(mx, wbucket[lb]);
		mx = max(mx, wbucket[rb]);
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
				wbucket[bi]++;
				pbucket[bi]++;
			}
			if (rb > lb) {
				mx = 0;
				int l_hi = (lb+1)*len;
				for (int i=l; i<l_hi; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				pbucket[lb] = max(pbucket[lb], mx);
				mx = 0;
				int r_lo = rb*len;
				for (int i=r_lo; i<=r; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				pbucket[rb] = max(pbucket[rb], mx);
			} else {
				mx = 0;
				for (int i=l; i<=r; i++) {
					aa[i]++;
					mx = max(mx, aa[i]);
				}
				pbucket[lb] = max(pbucket[lb], mx);
			}
		} else {
			printf("No\n");
		}
	}
	return 0;
}
