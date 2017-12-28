/* ACMP 1085 */
#include <stdio.h>
#include <string.h>
#include <memory.h>

// 2d fenwick
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int ff[n][n];
	memset(ff, 0, sizeof(ff));
	while (m-- > 0) {
		char cmd[8];
		scanf("%7s", cmd);
		if (strcmp(cmd, "add") == 0) {
			int x, y;
			scanf("%d%d", &x, &y);
			for (int i=x-1; i<n; i|=i+1)
				for (int j=y-1; j<n; j|=j+1)
					ff[i][j]++;
		} else if (strcmp(cmd, "rsq") == 0) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x1 -= 2, y1 -= 2, x2--, y2--;
			int s = 0;
			for (int i=y1; i>=0; i=(i&(i+1))-1)
				for (int j=x1; j>=0; j=(j&(j+1))-1)
					s += ff[i][j];
			for (int i=y2; i>=0; i=(i&(i+1))-1)
				for (int j=x2; j>=0; j=(j&(j+1))-1)
					s += ff[i][j];
			for (int i=y2; i>=0; i=(i&(i+1))-1)
				for (int j=x1; j>=0; j=(j&(j+1))-1)
					s -= ff[i][j];
			for (int i=y1; i>=0; i=(i&(i+1))-1)
				for (int j=x2; j>=0; j=(j&(j+1))-1)
					s -= ff[i][j];
			printf("%d\n", s);
		}
	}
	return 0;
}
