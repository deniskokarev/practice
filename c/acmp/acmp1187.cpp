/* ACMP 1187 */
#include <cstdio>
#include <cstring>
#include <cmath>

#define dim(X) (sizeof(X)/sizeof(X[0]))

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

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int pad = (1<<l2)-1;
	// must use perfect 2^n-1 tree
	unsigned aa[pad+(1<<l2)];
	for (int i=0; i<n; i++)
		scanf("%d", &aa[pad+i]);
	// must clone last element to keep gcd consistent at all levels
	for (int i=pad+n; i<dim(aa); i++)
		aa[i] = aa[i-1];
	for (int i=dim(aa)-1; i>0; i-=2)
		aa[(i-1)/2] = gcd(aa[i], aa[i-1]);
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		char cmd[32];
		int arg1, arg2;
		scanf("%31s%d%d", cmd, &arg1, &arg2);
		if (cmd[0] == 'g') {
			int l = pad + arg1 - 1;
			int r = pad + arg2 - 1;
			unsigned gl = aa[l], gr = aa[r];
			while (l<r) {
				if ((l&1) == 0)
					gl = gcd(gl, aa[l]);
				l = l/2;
				if ((r&1) == 1)
					gr = gcd(gr, aa[r]);
				r = r/2-1;
			}
			if (l == r)
				gl = gcd(gl, aa[l]);
			printf("%u ", gcd(gl, gr));
		} else if (cmd[0] == 'u') {
			int p = pad + arg1 - 1;
			unsigned g = arg2;
			aa[p] = g;
			for (int r=(p-1)/2; p>0; p=r,r=(p-1)/2) {
				if ((p&1) == 0)
					aa[r] = gcd(aa[p-1], aa[p]);
				else
					aa[r] = gcd(aa[p], aa[p+1]);
			}
		}
	}
	printf("\n");
	return 0;
}
