#include <cstdio>
#include <algorithm>
/* CodeForces CF1006D problem */
using namespace std;

bool isok(char *s) {
	sort(s, s+4);
	return (s[0]==s[1] && s[2]==s[3]);
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	char a[n+1], b[n+1];
	scanf("%s %s", a, b);
	int i, j;
	int ans = 0;
	for (i=0,j=n-1; i<j; i++,j--) {
		struct {
			char s[4];
			int repl;
		} aa[] = {
			{{a[i], a[j], b[i], b[j]}, 0},
			{{b[i], a[j], b[i], b[j]}, 1},
			{{b[j], a[j], b[i], b[j]}, 1},
			{{a[i], b[i], b[i], b[j]}, 1},
			{{a[i], b[j], b[i], b[j]}, 1},
			{{a[i], a[i], b[i], b[j]}, 1},
			{{a[j], a[j], b[i], b[j]}, 1},
			{{b[i], b[j], b[i], b[j]}, 2}
		};
		for (auto &a:aa) {
			if (isok(a.s)) {
				ans += a.repl;
				break;
			}
		}
	}
	if (i==j)
		ans += (a[i]!=b[i]);
	printf("%d\n", ans);
	return 0;
}
