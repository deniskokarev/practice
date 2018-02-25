/* ACMP 140 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			scanf("%d", &mm[i][j]);
			if (mm[i][j] > 10000)
				mm[i][j] = DINF;
		}
	}
	// ford
	int dd[n];
	fill(dd, dd+n, DINF);
	dd[0] = 0;
	for (int v=0; v<n; v++) {
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				dd[j] = min(dd[j], max(-DINF, dd[i]+mm[i][j]));
	}
	// one more ford iteration
	int savedd[n];
	copy(dd, dd+n, savedd);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			dd[j] = min(dd[j], max(-DINF, dd[i]+mm[i][j]));
	const char *ans = "NO";
	for (int i=0; i<n; i++)
		if (dd[i] == -DINF || savedd[i] > dd[i])
			ans = "YES";
	printf("%s\n", ans);
	return 0;
}
