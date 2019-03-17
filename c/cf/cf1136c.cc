#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1136C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int>> aadg(n+m-1, vector<int>());
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			int d;
			scanf("%d", &d);
			aadg[i+j].push_back(d);
		}
	}
	vector<vector<int>> bbdg(n+m-1, vector<int>());
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			int d;
			scanf("%d", &d);
			bbdg[i+j].push_back(d);
		}
	}
	bool ans = true;
	for (int k=0; k<n+m-1; k++) {
		sort(aadg[k].begin(), aadg[k].end());
		sort(bbdg[k].begin(), bbdg[k].end());
		for (int l=0; l<aadg[k].size(); l++)
			ans &= (aadg[k][l] == bbdg[k][l]);
	}
	printf("%s\n", ans?"YES":"NO");
	return 0;
}
