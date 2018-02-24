/* ACMP 137 */
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int mm[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			scanf("%d", &mm[i][j]);
	for (int i=0; i<n; i++)
		mm[i][i] = 1;
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j]*mm[i][k]*mm[k][j])
					mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
				else if (mm[i][k]*mm[k][j])
					mm[i][j] = mm[i][k]+mm[k][j];
	int savemm[n][n];
	memcpy(savemm, mm, sizeof(mm));
	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (mm[i][j]*mm[i][k]*mm[k][j])
					mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
				else if (mm[i][k]*mm[k][j])
					mm[i][j] = mm[i][k]+mm[k][j];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			if (mm[i][j] < savemm[i][j])
				mm[i][j] = 2;
			else if (mm[i][j])
				mm[i][j] = 1;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++)
			printf("%d ", mm[i][j]);
		printf("\n");
	}
	return 0;
}
