/* ACMP 1375 */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	int s, e;
	scanf("%d %d %d %d", &n, &m, &s, &e);
	s--, e--;
	struct {
		int conn;
		double prob;
	} mm[n][n];
	memset(mm, 0, sizeof(mm));
	for (int i=0; i<n; i++)
		mm[i][i] = {1, 0};
	while (m--) {
		int i, j;
		int p;
		scanf("%d %d %d", &i, &j, &p);
		i--, j--;
		mm[i][j].conn = 1;
		mm[i][j].prob = ((double)p)/100.0;
		mm[j][i] = mm[i][j];
	}
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j].conn && (mm[i][k].conn && mm[k][j].conn))
					mm[i][j] = { 1, min(mm[i][j].prob, 1.0-(1.0-mm[i][k].prob)*(1.0-mm[k][j].prob)) };
				else if (mm[i][k].conn && mm[k][j].conn)
					mm[i][j] = { 1, 1.0-(1.0-mm[i][k].prob)*(1.0-mm[k][j].prob) };
	printf("%.6f\n", mm[s][e].prob);
	return 0;
}
