/* ACMP 1376 */
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int DINF = INT_MAX/2;

struct N {
	int conn;
	int w;
	int to;
	int id;
};

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	N mm[n][n];
	memset(mm, 0, sizeof(mm));
	for (int id=0; id<m; id++) {
		int i, j, w;
		scanf("%d %d %d", &i, &j, &w);
		i--, j--;
		mm[i][j] = {1, w, j, id};
	}
	// floyd
	for (int k=0; k<n; k++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				int ndist = min(DINF, mm[i][k].w+mm[k][j].w);
				if (mm[i][j].conn && mm[i][k].conn && mm[k][j].conn) {
					if (mm[i][j].w < ndist)
						mm[i][j] = {1, ndist, mm[i][k].to, mm[i][k].id}; 
				} else if (mm[i][k].conn && mm[k][j].conn) {
					mm[i][j] = {1, ndist, mm[i][k].to, mm[i][k].id};
				}
			}
		}
	}
	N savemm[n][n];
	memcpy(savemm, mm, sizeof(mm));
	// floyd again to reliably detect pos loops 
	for (int k=0; k<n; k++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				int ndist = min(DINF, mm[i][k].w+mm[k][j].w);
				if (mm[i][j].conn && mm[i][k].conn && mm[k][j].conn) {
					if (mm[i][j].w < ndist)
						mm[i][j] = {1, ndist, mm[i][k].to, mm[i][k].id}; 
				} else if (mm[i][k].conn && mm[k][j].conn) {
					mm[i][j] = {1, ndist, mm[i][k].to, mm[i][k].id};
				}
			}
		}
	}
	for (int i=0; i<n; i++)
		if (mm[i][i].w > savemm[i][i].w)
			savemm[i][i].conn = 2; // mark loops
	memcpy(mm, savemm, sizeof(mm));
	vector<int> path;
	int t;
	scanf("%d", &t);
	t--, k--;
	while (k--) {
		int f = t;
		scanf("%d", &t);
		t--;
		int n = f;
		while (n != t) {
			if (mm[n][n].conn == 2) {
				printf("infinitely kind\n");
				goto end;
			}	
			path.push_back(mm[n][t].id);
			n = mm[n][t].to;
		}
		if (mm[n][n].conn == 2) {
			printf("infinitely kind\n");
			goto end;
		}	
	}
	printf("%d\n", (int)path.size());
	for (auto p:path)
		printf("%d ", p+1);
	printf("\n");
 end:
	return 0;
}
