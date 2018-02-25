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
	// ford
	int dd[n+1];
	fill(dd, dd+n+1, DINF);
	int f=1;
	dd[f] = 0;
	for (int v=1; v<=n; v++)
		for (int i=1; i<=n; i++)
			for (int j=i+1; j<=n; j++)
				dd[j] = min(dd[j], dd[i]+w(i, j));
	printf("%d\n", dd[n]);
	return 0;
}
