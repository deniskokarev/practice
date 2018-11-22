#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1061C problem */
using namespace std;

constexpr int MXF = 1000;
constexpr int64_t MOD = 1e9+7;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> aa(n);
	for (auto &a:aa)
		scanf("%d", &a);
	if (n < 2) {
		printf("1\n");
	} else {
		vector<int64_t> ff(1000000+2);
		int i = n-1;
		for (int f=1; f<=MXF; f++)
			if (aa[i] % f == 0)
				ff[f] = ff[aa[i]/f] = 1;
		vector<pair<int,int>> nv(2002);
		for (int i=n-2; i>=0; i--) {
			int f;
			int nvsz = 0;
			for (f=1; f*f<=aa[i]; f++) {
				if (aa[i] % f == 0) {
					int q = aa[i] / f;
					nv[nvsz++] = make_pair(f, (1 + ff[f+1] + ff[f]) % MOD);
					nv[nvsz++] = make_pair(q, (1 + ff[q+1] + ff[q]) % MOD);
				}
			}
			for (int i=0; i<nvsz; i++)
				ff[nv[i].first] = nv[i].second;
		}
		printf("%d\n", int(ff[1]));
	}
	return 0;
}
