/* ACMP 1181 */
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
	memset(bucket, 0, sizeof(bucket));
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		aa[i] = (a == 0);
		int bi = i/b;
		bucket[bi] += aa[i];
	}
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		int lb = l/b;
		int rb = r/b;
		int sum = 0;
		if (rb-lb > 1) {
			for (int bi=lb+1; bi<rb; bi++)
				sum += bucket[bi];
			int l_hi = (lb+1)*b;
			for (int i=l; i<l_hi; i++)
				sum += aa[i];
			int r_lo = rb*b;
			for (int i=r_lo; i<=r; i++)
				sum += aa[i];
		} else {
			for (int i=l; i<=r; i++)
				sum += aa[i];
		}
		printf("%d ", sum);
	}
	printf("\n");
	return 0;
}
