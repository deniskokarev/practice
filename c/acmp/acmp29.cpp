/* ACMP 29 */
#include <limits.h>
#include <stdio.h>

unsigned abs_diff(unsigned a, unsigned b) {
	return (a>b)?a-b:b-a;
}

unsigned min(unsigned a, unsigned b) {
	return (a<b)?a:b;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	unsigned yy[n+2];
	for (int i=0; i<n; i++)
		scanf("%d", &yy[i]);
	unsigned ee[n+2];
	ee[0] = 0;
	for (int i=1; i<=n; i++)
		ee[i] = INT_MAX;
	for (int i=0; i<n; i++) {
		ee[i+1] = min(ee[i+1], ee[i]+abs_diff(yy[i+1], yy[i]));
		ee[i+2] = min(ee[i+2], ee[i]+3*abs_diff(yy[i+2], yy[i]));
	}
	printf("%u\n", ee[n-1]);
	return 0;
}
