#include <cstdio>
#include <algorithm>
/* ACMP 20 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (auto &a:aa)
		scanf("%d", &a);
	int sign[2] = {-1, 1};
	int mx = 0;
	for (auto s:sign) {
		int l = 0;
		int o = s;
		for (int i=1; i<n; i++) {
			if (aa[i-1]*o < aa[i]*o) {
				if (l == 0)
					l = 2;
				else
					l++;
				mx = max(mx, l);
			} else {
				l = 0;
			}
			o *= -1;
		}
	}
	printf("%d\n", mx);
	return 0;
}
