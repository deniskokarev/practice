/* ACMP 283 */
#include <cstdio>
#include <algorithm>

int main(int argc, char **argv) {
	int sz[6] = {0};
	int ch;
	int ln = 0;
	while ((ch=fgetc(stdin)) > 0) {
		if (ch == '\n')
			break;
		if (ch>='A' && ch<='Z') {
			if (ln > 4) {
				sz[5]++;
				break;
			}
			sz[ln]++;
			ln = 0;
		} else {
			ln++;
		}
	}
	sz[std::min(ln, 5)]++;
	if (sz[0] == 1 && sz[5] == 0 && sz[1]+sz[2]+sz[3] > 0)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
