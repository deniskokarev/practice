/* ACMP 1377 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

static int w(int i, int j) {
	return (179*i + 719*j)%1000 - 500;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	// a-la ford, only backwards and with O(n^2), as we have a DAG
	int dd[n+1];
	fill(dd, dd+n+1, DINF);
	dd[n] = 0;
	for (int f=n-1; f>0; f--)
		for (int t=f+1; t<=n; t++)
			dd[f] = min(dd[f], dd[t]+w(f, t));
	printf("%d\n", dd[1]);
	return 0;
}
