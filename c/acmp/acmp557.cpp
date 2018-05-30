#include <stdio.h>
#include <vector>
/* ACMP 557 */
using namespace std;
 
int main(int argc, char **argv) {
	int m, n;
	scanf("%d%d", &m, &n);
	int a, b;
	scanf("%d%d", &a, &b);
	int p;
	scanf("%d", &p);
	vector<vector<vector<int>>> mmm(m, vector<vector<int>>(n, vector<int>(n)));
	for (int mi=0; mi<m; mi++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				scanf("%d", &mmm[mi][i][j]);
	vector<vector<int>> cc(n, vector<int>(n));
	for (int mi=0; mi<m-1; mi++) {
		int i = a-1;
		for (int j=0; j<n; j++) {
			int e = 0;
			for (int k=0; k<n; k++)
				e += mmm[mi][i][k]*mmm[mi+1][k][j];
			cc[i][j] = e % p;
		}
		mmm[mi+1].swap(cc);
	}
	printf("%d\n", mmm[m-1][a-1][b-1]);
	return 0;
}
