#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
/* ACMP 1690 */
using namespace std;

int main(int argc, char **argv) {
	int h, n, m, q;
	fscanf(stdin, "%d%d%d%d\n", &h, &n, &m, &q);
	vector<vector<vector<int>>> mat(h+1, vector<vector<int>>(n+1, vector<int>(m+1)));
	for (int x=1; x<=h; x++) {
		for (int y=1; y<=n; y++) {
			char s[m+1];
			fread(s, 1, m+1, stdin);
			for (int z=1; z<=m; z++)
				mat[x][y][z] = s[z-1]-'0';
		}
		fgetc(stdin); // \n
	}
	for (int x=1; x<=h; x++)
		for (int y=1; y<=n; y++)
			for (int z=1; z<=m; z++)
				mat[x][y][z] += mat[x-1][y][z] + mat[x][y-1][z] + mat[x][y][z-1] - mat[x-1][y-1][z] - mat[x-1][y][z-1] - mat[x][y-1][z-1] + mat[x-1][y-1][z-1];
	//fprintf(stderr, "sm=%d\n", mat[h][n][m]);
	while (q--) {
		int x1,y1,z1, x2,y2,z2;
		fscanf(stdin, "%d%d%d%d%d%d\n", &x1, &y1, &z1, &x2, &y2, &z2);
		// must "normalize" corners
		if (x1 > x2)
			swap(x1, x2);
		if (y1 > y2)
			swap(y1, y2);
		if (z1 > z2)
			swap(z1, z2);
		x1--, y1--, z1--;
		int res = mat[x2][y2][z2] - mat[x1][y2][z2] - mat[x2][y1][z2] - mat[x2][y2][z1] + mat[x1][y1][z2] + mat[x1][y2][z1] + mat[x2][y1][z1] - mat[x1][y1][z1];
		fprintf(stdout, "%d\n", res);
	}
	return 0;
}
