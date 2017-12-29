/* ACMP 1178 */
#include <stdio.h>
#include <memory.h>
#include <assert.h>

constexpr int MXHT = 1e5;

enum {
	CMD_INS = 1,
	CMD_REM = 2
};

#define dim(X)	(sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int fw[MXHT+1];
	memset(fw, 0, sizeof(fw)); // rev order (solder height 100000 stands at 0)
	int n;
	scanf("%d", &n);
	while (n-- > 0) {
		int cmd, arg;
		scanf("%d%d", &cmd, &arg);
		assert(arg > 0 && arg <= MXHT);
		int rp = MXHT-arg;	// rev pos
		int npeople = 0;
		switch (cmd) {
		case CMD_INS:
			for (int i=rp; i>=0; i=(i&(i+1))-1)
				npeople += fw[i];
			printf("%d\n", npeople);
			for (int i=rp; i<dim(fw); i|=i+1)
				fw[i]++;
			break;
		case CMD_REM:
			for (int i=rp; i<dim(fw); i|=i+1)
				fw[i]--;
			break;
		}
	}
	return 0;
}
