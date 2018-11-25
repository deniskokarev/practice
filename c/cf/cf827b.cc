#include <cstdio>
#include <algorithm>
/* CodeForces CF827B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	int r = n-k-1;
	int hi = (r+k-1)/k+1;
	int lo = r/k+1;
	int ans;
	if (n-hi-1 == (k-1)*lo)
		ans = hi+lo;
	else
		ans = hi+hi;
	printf("%d\n", ans);
	int l;
	for (l=0; l<lo; l++)
		for (int i=1; i<=k; i++)
			printf("%d %d\n", l*k+i, min((l+1)*k+i, n));
	for (int i=1; i<=k && l*k+i < n; i++)
		printf("%d %d\n", l*k+i, n);
	return 0;
}
