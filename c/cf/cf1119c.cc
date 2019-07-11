#include <cstdio>
#include <vector>
/* CodeForces CF1119C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int>> aa(n, vector<int>(m));
	vector<vector<int>> bb(n, vector<int>(m));
	for (int r=0; r<n; r++)
		for (int c=0; c<m; c++)
			scanf("%d", &aa[r][c]);
	for (int r=0; r<n; r++)
		for (int c=0; c<m; c++)
			scanf("%d", &bb[r][c]);
	for (int r=0; r<n-1; r++) {
		for (int c=0; c<m-1; c++) {
			if (aa[r][c]) {
				aa[r][c] ^= 1;
				aa[r+1][c] ^= 1;
				aa[r][c+1] ^= 1;
				aa[r+1][c+1] ^= 1;
			}
			if (bb[r][c]) {
				bb[r][c] ^= 1;
				bb[r+1][c] ^= 1;
				bb[r][c+1] ^= 1;
				bb[r+1][c+1] ^= 1;
			}
		}
	}
	bool ans = true;
	for (int r=0; r<n; r++)
		ans &= (aa[r][m-1] == bb[r][m-1]);
	for (int c=0; c<m; c++)
		ans &= (aa[n-1][c] == bb[n-1][c]);
	printf("%s\n", ans?"Yes":"No");
	return 0;
}
