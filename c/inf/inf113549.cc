#include <cstdio>
#include <climits>
#include <algorithm>
/* ROI 2017 F */
using namespace std;

struct W {
	int lo, hi;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int tt[n];
	for (int &t:tt)
		scanf("%d", &t);
	W ww[n-1]; // walls
	for (auto &w:ww)
		scanf("%d%d", &w.lo, &w.hi);
	if (n < 2) {
		printf("0\n");
		return 0;
	}
	W ll[n]; // left->right
	int i = n-1;
	ll[i].lo = max(ww[i-1].lo-tt[i], 0);
	ll[i].hi = ww[i-1].hi;
	i--;
	while (i >= 0) {
		int lo = max(ll[i+1].lo, ww[i].lo);
		int hi = min(ll[i+1].hi, ww[i].hi);
		if (lo <= hi)
			ll[i] = {max(0, lo-tt[i]), hi};
		else
			ll[i] = {INT_MAX, 0};
		i--;
	}
	W rr[n]; // right->left
	i = 0;
	rr[i].lo = max(ww[i].lo-tt[i], 0);
	rr[i].hi = ww[i].hi;
	i++;
	while (i < n) {
		int lo = max(rr[i-1].lo, ww[i-1].lo);
		int hi = min(rr[i-1].hi, ww[i-1].hi);
		if (lo <= hi)
			rr[i] = {max(0, lo-tt[i]), hi};
		else
			rr[i] = {INT_MAX, 0};
		i++;
	}
	for (int i=0; i<n; i++)
		if (ll[i].lo <= ll[i].hi && rr[i].lo <= rr[i].hi)
			printf("%d\n", max(ll[i].lo, rr[i].lo));
		else
			printf("%d\n", -1);
	return 0;
}
