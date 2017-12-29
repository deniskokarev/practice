/* ACMP 1178 */
#include <stdio.h>
#include <memory.h>
#include <assert.h>

/**
 * Plain C-style Fenwick implementation
 */
static void fw_init(int *fw, int sz) {
	memset(fw, 0, sizeof(fw[0])*sz);
}

static void fw_upd(int *fw, int p, int inc, int sz) {
	for (int i=p; i<sz; i|=i+1)
		fw[i] += inc;
}

static int fw_sum(int *fw, int p, int sz) {
	int sum = 0;
	for (int i=p; i>=0; i=(i&(i+1))-1)
		sum += fw[i];
	return sum;
}

#define dim(X)	(sizeof(X)/sizeof(X[0]))

#define MXHT  100000

enum {
	CMD_INS = 1,
	CMD_REM = 2
};

int main(int argc, char **argv) {
	int fw[MXHT+1];		 // rev order (solder height 100000 stands at 0)
	fw_init(fw, dim(fw));
	int n;
	scanf("%d", &n);
	while (n-- > 0) {
		int cmd, arg;
		scanf("%d%d", &cmd, &arg);
		assert(arg >= 0 && arg <= MXHT);
		int rp = MXHT-arg;	// rev pos
		int f, t;
		switch (cmd) {
		case CMD_INS:
			printf("%d\n", fw_sum(fw, rp-1, dim(fw)));
			fw_upd(fw, rp, 1, dim(fw));
			break;
		case CMD_REM:
			// lower_bound binary search
			f = 0, t = dim(fw);
			arg++;
			while (f<t) {
				int m = f+(t-f)/2;
				if (fw_sum(fw, m, dim(fw)) < arg)
					f = m+1;
				else
					t = m;
  			}
			fw_upd(fw, f, -1, dim(fw));
			break;
		}
	}
	return 0;
}
