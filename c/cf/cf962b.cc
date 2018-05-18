#include <cstdio>
/* CodeForces CF962B problem */
using namespace std;

enum {
	A, B
};

int main(int argc, char **argv) {
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	char s[200002];
	s[0] = '*';
	scanf("%200000s", s+1);
	int was = a+b;
	for (int i=1; i<=n; i++) {
		if (s[i] == '.') {
			if (s[i-1] == A) {
				if (b > 0) {
					b--;
					s[i] = B;
				}
			} else if (s[i-1] == B) {
				if (a > 0) {
					a--;
					s[i] = A;
				}
			} else {
				if (a > b) {
					a--;
					s[i] = A;
				} else if (b > 0) {
					b--;
					s[i] = B;
				}
			}
		}
	}
	printf("%d\n", was-a-b);
	return 0;
}
