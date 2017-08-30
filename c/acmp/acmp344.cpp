#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>

/* ACMP 344 problem */

using namespace std;

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<pair<int,int>> xx(n);
	for (int i=0; i<n; i++) {
		xx[i].second = i+1;
		scanf("%d", &xx[i].first);
	}
	sort(xx.begin(), xx.end());
	int mn = INT_MAX;
	int mni = -1;
	for (int i=0; i<n-1; i++) {
		int d = xx[i+1].first - xx[i].first;
		if (d < mn) {
			mni = i;
			mn = d;
		}
	}
	printf("%d\n%d %d\n", mn, xx[mni].second, xx[mni+1].second);
	return 0;
}
