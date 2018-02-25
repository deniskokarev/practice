/* ACMP 138 */
#include <cstdio>
#include <climits>
#include <vector>

using namespace std;

constexpr int DINF = INT_MAX/2;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<int>> mm(n, vector<int>(n, DINF));
	while (m--) {
		int i, j, w;
		scanf("%d%d%d", &i, &j, &w);
		i--, j--;
		mm[i][j] = min(mm[i][j], w);
	}
	for (int i=0; i<n; i++)
		mm[i][i] = 0;
	// ford
	int f=0;
	vector<int> dd(mm[f]);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			dd[j] = min(dd[j], dd[i]+mm[i][j]);
	for (auto d:dd)
		printf("%d ", (d<30000)?d:30000);
	printf("\n");
	return 0;
}
