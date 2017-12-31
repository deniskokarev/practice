/* ACMP 1183 */
#include <stdio.h>
#include <memory.h>
#include <math.h>

/**
 * GCD(a, b) - greatest common divisor
 */
unsigned gcd(unsigned a, unsigned b) {
	while (b > 0) {
		unsigned temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int sz = (1 << l2) - 1; // interval tree size
	unsigned aa[sz+(1<<l2)];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++)
		scanf("%d", &aa[sz+i]);
	for (int i=n; i<(1<<l2); i++)
		aa[sz+i] = aa[sz+i-1];
	for (int i=dim(aa)-1; i>0; i-=2) {
		int r = (i-1)/2;
		aa[r] = gcd(aa[i-1], aa[i]);
	}
	int m;
	scanf("%d", &m);
	while(m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l += sz-1;
		r += sz-1;
		int ansl = aa[l];
		int ansr = aa[r];
		while (l<r) {
			if ((l&1) == 0)
				ansl = gcd(ansl, aa[l]);
			l = l/2;
			if ((r&1) == 1)
				ansr = gcd(ansr, aa[r]);
			r = (r-2)/2;
		}
		if (l == r)
			ansl =  gcd(ansl, aa[l]);
		printf("%d ", gcd(ansl, ansr));
	}
	printf("\n");
	return 0;
}
