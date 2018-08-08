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
	int mx = 0;
	for (auto sign:{-1, 1}) {
		for (auto ofs:{1, 2}) {
			int l = 0;
			for (int i=ofs,op=sign; i<n; i++,op*=-1) {
				if (aa[i-1]*op < aa[i]*op) {
					if (l == 0)
						l = 2;
					else
						l++;
					mx = max(mx, l);
				} else {
					l = 0;
				}
			}
		}
	}
	printf("%d\n", mx);
	return 0;
}
