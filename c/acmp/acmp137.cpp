/* ACMP 137 */
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

struct N {
	int conn;
	int dist;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	N mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			scanf("%d", &mm[i][j].dist);
			mm[i][j].conn = (i==j) || (mm[i][j].dist != 0);
		}
	}
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j].conn && mm[i][k].conn && mm[k][j].conn)
					mm[i][j] = {1, min(mm[i][j].dist, mm[i][k].dist+mm[k][j].dist)};
				else if (mm[i][k].conn && mm[k][j].conn)
					mm[i][j] = {1, mm[i][k].dist+mm[k][j].dist};
	N savemm[n][n];
	memcpy(savemm, mm, sizeof(mm));
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j].conn && mm[i][k].conn && mm[k][j].conn)
					mm[i][j] = {1, min(mm[i][j].dist, mm[i][k].dist+mm[k][j].dist)};
				else if (mm[i][k].conn && mm[k][j].conn)
					mm[i][j] = {1, mm[i][k].dist+mm[k][j].dist};
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j].dist < savemm[i][j].dist)
				mm[i][j].conn = 2;
			else if (mm[i][j].dist)
				mm[i][j].conn = 1;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			printf("%d ", mm[i][j].conn);
		printf("\n");
	}
	return 0;
}
