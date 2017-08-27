/* ACMP 119 */
#include <stdio.h>

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (int i=0; i<n; i++) {
		int h, m, s;
		scanf("%d %d %d", &h, &m, &s);
		aa[i] = s + m*60 + h*3600;
	}
	for (int i=0; i<n-1; i++) {
		for (int j=0; j<n-1; j++) {
			if (aa[j] > aa[j+1]) {
				int b = aa[j];
				aa[j] = aa[j+1];
				aa[j+1] = b;
			}
		}
	}
	for (int i=0; i<n; i++)
		printf("%d %d %d\n", aa[i]/3600, (aa[i]/60)%60, (aa[i])%60); 
	return 0;
}

