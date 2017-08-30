/* ACMP 41 problem */

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
	unsigned tt[201];
	memset(tt, 0, sizeof(tt));
	unsigned n;
	scanf("%u", &n);
	for (int i=0; i<n; i++) {
		int t;
		scanf("%d", &t);
		assert(t >= -100 && t <= 100);
		tt[t+100]++;
	}
	for (int t=-100; t<=100; t++)
		for (int j=0; j<tt[t+100]; j++)
			printf("%d ", t);
	printf("\n");
	return 0;
}
