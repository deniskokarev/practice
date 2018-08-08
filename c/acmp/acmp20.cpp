#include <stdio.h>
#include <algorithm>
/* ACMP 20 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (auto &a:aa)
		scanf("%d", &a);
	int mx = 1;
	for (auto sign:{-1, 1}) {
		int l = 1;
		for (int i=1,op=sign; i<n; i++,op*=-1) {
			if (aa[i-1]*op < aa[i]*op)
				l++;
			else
				l = 1;
			mx = max(mx, l);
		}
	}
	printf("%d\n", mx);
	return 0;
}
