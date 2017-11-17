/* ACMP 1154 */
#include <stdio.h>

int main(int argc, char **argv) {
	int o[4];
	char c[5];
	bool rc = false;
	if (scanf("%d%[.]%d%[.]%d%[.]%d%[\n]", &o[0], &c[0], &o[1], &c[1], &o[2], &c[2], &o[3], &c[3]) == 8) {
		if (c[3] == '\n') {
			for (auto d:o)
				if (d<0 || d>255)
					goto end;
			rc = true;
		}
	}
 end:
	printf("%s\n", (rc?"Good":"Bad"));
	return 0;
}
