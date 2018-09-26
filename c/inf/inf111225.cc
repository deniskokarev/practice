#include <cstdio>
#include <vector>
#include <array>
/* ROI 2012E problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<array<int,2>> ee(n+1);
	for (int i=1; i<=n; i++)
		scanf("%d%d", &ee[i][0], &ee[i][1]);
	// than's to Fedor
	// to find a pair of 2-element tuples where both elements are different
	// it is sufficient to look at three touples where .first or .second are different
	vector<array<int,2>> rr(n+1); // closest diff to the right
	rr[n][0] = rr[n][1] = n+1;
	for (int i=n-1; i>=1; i--)
		for (int j=0; j<2; j++)
			if (ee[i][j] != ee[i+1][j])
				rr[i][j] = i+1;
			else
				rr[i][j] = rr[i+1][j];
	int k;
	scanf("%d", &k);
	while (k--) {
		int l, r;
		scanf("%d%d\n", &l, &r);
		int pp[3] = {l, min(rr[l][0], rr[l][1]), max(rr[l][0], rr[l][1])};
		if (pp[2] > r) {
			printf("0 0\n");
		} else {
			for (int i=0; i<3; i++) {
				int j = (i+1)%3;
				if (ee[pp[i]][0] != ee[pp[j]][0] && ee[pp[i]][1] != ee[pp[j]][1]) {
					printf("%d %d\n", pp[i], pp[j]);
					break;
				}
			}
		}
	}
	return 0;
}
