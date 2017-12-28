/* ACMP 1084 */
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	long long ff[n];
	for (int i=0; i<n;i++)
		ff[i] = 0;
	while (m-- > 0) {
		char cmd[8];
		int a1, a2;
		scanf("%7s%d%d", cmd, &a1, &a2);
		if (strcmp(cmd, "add") == 0) {
			for (int i=a1-1; i<n; i|=i+1)
				ff[i] += a2;
		} else if (strcmp(cmd, "rsq") == 0) {
			long long s = 0;
			for (int i=a2-1; i>=0; i=(i&(i+1))-1)
				s += ff[i];
			for (int i=a1-2; i>=0; i=(i&(i+1))-1)
				s -= ff[i];
			// screwie ACMP printf doesn't work well with %lld
			if (s>1000000000)
				printf("%d%09d\n", (int)(s/1000000000LL), (int)(s%1000000000LL));
			else
				printf("%d\n", (int)s);
		}
	}
	return 0;
}
