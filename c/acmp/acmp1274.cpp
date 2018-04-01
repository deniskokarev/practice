/* ACMP 1274 */
#include <stdio.h>
#include <limits.h>

#define max(A,B) ((A>B)?A:B)
#define min(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	int n, s;
	scanf("%d%d", &n, &s);
	int cc[n];
	for (auto &c:cc)
		scanf("%d", &c);
	int mn, mx;
	mn = mx = cc[0];
	int mxend = s;
	for (int i=1; i<n; i++) {
		if (cc[i] > mx)
			mx = cc[i];
		if (cc[i] < mn) {
			mn = cc[i];
			mx = mn;
		}
		int end = mx*(s/mn)+s%mn;
		mxend = max(mxend, end);
	}
	mn = mx = cc[0];
	int mnend = s;
	for (int i=1; i<n; i++) {
		if (cc[i] > mx) {
			mx = cc[i];
			mn = mx;
		}
		if (cc[i] < mn)
			mn = cc[i];
		int end = mn*(s/mx)+s%mx;
		mnend = min(mnend, end);
	}
	printf("%d %d\n", mnend, mxend);
	return 0;
}
