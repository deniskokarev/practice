#include <cstdio>
#include <vector>
#include <climits>
/* ROI 2018E */

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	std::vector<int> aa(n+2);
	aa[0] = INT_MIN;
	aa[n+1] = INT_MAX;
	for (int i=1; i<=n; i++)
		scanf("%d", &aa[i]);
	std::vector<int> cl(n+2), cr(n+2); // left and right cuts
	for (int p2=1; p2/2<n; p2*=2) { // ceil(log2(n+1)) passes must be enough
		int mn = aa[1];
		for (int i=1; i<=n; i++) {
			if (aa[i]<mn) {
				cl[i] = 1;
				mn = aa[i];
			} else if (cr[i]) {
				mn = aa[i+1];
			}
		}
		int mx = aa[n];
		for (int i=n; i>=1; i--) {
			if (aa[i]>mx) {
				cr[i] = 1;
				mx = aa[i];
			} else if (cl[i]) {
				mx = aa[i-1];
			}
		}
	}
	int ans = 0;
	for (int i=1; i<=n; i++)
		ans += cl[i]|cr[i];
	printf("%d\n", ans+1);
	return 0;
}
