/* ACMP 138 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

struct E {
	int i, j, w;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d %d", &n, &m);
	// ford
	E ee[m];
	for (int ei=0; ei<m; ei++)
		scanf("%d%d%d", &ee[ei].i, &ee[ei].j, &ee[ei].w);
	int dd[n+1];
	fill(dd, dd+n+1, DINF);
	int f=1;
	dd[f] = 0;
	for (int i=1; i<n; i++)
		for (int ei=0; ei<m; ei++)
			dd[ee[ei].j] = min(dd[ee[ei].j], dd[ee[ei].i]+ee[ei].w);
	for (int j=1; j<=n; j++)
		printf("%d ", (dd[j]<30000)?dd[j]:30000);
	printf("\n");
	return 0;
}
