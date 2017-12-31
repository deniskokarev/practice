/* ACMP 1184 */
#include <cstdio>
#include <cmath>
#include <climits>

#define dim(X) (sizeof(X)/sizeof(X[0]))

struct E {
	int val;
	int pos;
};

inline const E &max(const E &a, const E &b) {
	return (a.val >= b.val)?a:b;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int l2 = ceil(log2(n));
	int pad = (1<<l2)-1;
	E aa[pad+(n+1)/2*2];
	aa[dim(aa)-1] = E {INT_MIN, -1}; // init last el if the number is odd
	for (int i=0; i<n; i++) {
		scanf("%d", &aa[pad+i].val);
		aa[pad+i].pos = i;
	}
	for (int i=dim(aa)-1; i>0; i-=2)
		aa[(i-1)/2] = max(aa[i-1], aa[i]);
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l += pad - 1;
		r += pad - 1;
		E mxl = aa[l], mxr = aa[r];
		while (l<r) {
			if ((l&1) == 0)
				mxl = max(mxl, aa[l]);
			l = l/2;
			if ((r&1) == 1)
				mxr = max(aa[r], mxr);
			r = r/2-1;
		}
		if (l == r)
			mxl = max(mxl, aa[l]);
		E ans = max(mxl, mxr);
		printf("%d %d\n", ans.val, ans.pos+1);
	}
	return 0;
}
