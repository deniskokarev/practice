#include <stdio.h>
/* ACMP 197 */

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	short mm[n][n];
	int i = 0, j = 0;
	int dir = 1;
	int t = 1;
	for (int w=0; w<n; w++,dir*=-1) {
		while (i>=0 && j>=0) {
			mm[i][j] = t++;
			i += dir;
			j -= dir;
		}
		i += (dir<0);
		j += (dir>0);
	}
	j -= dir;
	i += dir;
	for (int w=0; w<n; w++,dir*=-1) {
		while (i<n && j<n) {
			mm[i][j] = t++;
			i += dir;
			j -= dir;
		}
		i += (dir<0)*2-(dir>0);
		j += (dir>0)*2-(dir<0);
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			printf("%hd ", mm[i][j]);
		printf("\n");
	}
	return 0;
}
