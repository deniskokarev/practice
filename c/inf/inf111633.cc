#include <cstdio>
#include <vector>
/* ROI 2013 A https://informatics.msk.ru/mod/statements/view3.php?id=7334&chapterid=111633 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<vector<int>> ee(n);
	for (int i=0; i<n; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		ee[f].push_back(t);
		ee[t].push_back(f);
	}
	vector<int> color(n);
	vector<int> qq(n);
	int col = 1;
	vector<vector<int>> vc(n+1);
	for (int i=0; i<n; i++) {
		if (!color[i]) {
			int qh=0, qt=0;
			qq[qt++] = i;
			color[i] = col;
			vc[col].push_back(i);
			while (qh<qt) {
				int r = qq[qh++];
				int acol = ((color[r]-col)^1)+col;
				for (int chld:ee[r]) {
					if (!color[chld]) {
						qq[qt++] = chld;
						color[chld] = acol;
						vc[acol].push_back(chld);
					}
				}
			}
			col += 2;
		}
	}
	vector<int> res(n);
	int res_sz = 0;
	for (int c=1; c<n; c+=2) {
		int mnc;
		if (vc[c].size() <= vc[c+1].size())
			mnc = c;
		else
			mnc = c+1;
		for (auto v:vc[mnc])
			res[res_sz++] = v+1;
	}
#if 0
	for (int i=0; i<res_sz; i++)
		fprintf(stderr, "%d ", res[i]);
	fprintf(stderr, "\n");
#endif
	int k;
	scanf("%d", &k);
	if (res_sz < k) {
		printf("0\n");
	} else {
		for (int i=0; i<k; i++)
			printf("%d ", res[i]);
		printf("\n");
	}
	return 0;
}
