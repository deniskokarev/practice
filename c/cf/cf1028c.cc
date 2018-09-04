#include <stdio.h>
#include <algorithm>
#include <vector>
/* CodeForces CF1028C problem */
using namespace std;

struct R {
	int x1, y1;
	int x2, y2;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<R> rr(n+2);
	for (int i=1; i<=n; i++)
		scanf("%d%d%d%d", &rr[i].x1, &rr[i].y1, &rr[i].x2, &rr[i].y2);
	vector<R> l2r(n+2);
	l2r[0] = R {INT_MIN, INT_MIN, INT_MAX, INT_MAX};
	for (int i=1; i<=n; i++) {
		l2r[i].x1 = max(l2r[i-1].x1, rr[i].x1);
		l2r[i].y1 = max(l2r[i-1].y1, rr[i].y1);
		l2r[i].x2 = min(l2r[i-1].x2, rr[i].x2);
		l2r[i].y2 = min(l2r[i-1].y2, rr[i].y2);
	}
	vector<R> r2l(n+2);
	r2l[n+1] = R {INT_MIN, INT_MIN, INT_MAX, INT_MAX};
	for (int i=n; i>=1; i--) {
		r2l[i].x1 = max(r2l[i+1].x1, rr[i].x1);
		r2l[i].y1 = max(r2l[i+1].y1, rr[i].y1);
		r2l[i].x2 = min(r2l[i+1].x2, rr[i].x2);
		r2l[i].y2 = min(r2l[i+1].y2, rr[i].y2);
	}
	for (int i=1; i<=n; i++) {
		R r {
			max(l2r[i-1].x1, r2l[i+1].x1),
			max(l2r[i-1].y1, r2l[i+1].y1),
			min(l2r[i-1].x2, r2l[i+1].x2),
			min(l2r[i-1].y2, r2l[i+1].y2)
		};
		if (r.x1 <= r.x2 && r.y1 <= r.y2) {
			printf("%d %d\n", r.x1, r.y1);
			break;
		}
	}
	return 0;
}
