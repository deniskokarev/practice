/* ACMP 283 */
#include <cstdio>
#include <algorithm>

int main(int argc, char **argv) {
	int sz[6] = {0};
	int ch;
	int ln = 0;
	while ((ch=fgetc(stdin)) > 0 && isalpha(ch)) {
		if (ch>='A' && ch<='Z') {
			if (ln >= 0 && ln < 5)
				sz[ln]++;
			else
				sz[5]++;
			ln = 0;
		}
		ln++;
	}
	sz[std::min(ln, 5)]++;
	if (sz[0] == 1 && sz[1] == 0 && sz[5] == 0 && sz[2]+sz[3]+sz[4] > 0)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
