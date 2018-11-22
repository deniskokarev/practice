#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1061C problem */
using namespace std;

constexpr int MXF = 1000;
constexpr int MOD = 1e9+7;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> aa(n);
	for (auto &a:aa)
		scanf("%d", &a);
	if (n < 2) {
		printf("1\n");
	} else {
		vector<vector<int>> ff(2, vector<int>(MXF+2));
		int i = n-1;
		for (int f=1; f<=MXF; f++)
			ff[i&1][f] = (aa[i] % f == 0);
		for (int i=n-2; i>=0; i--)
			for (int f=MXF; f>0; f--)
				if (aa[i] % f == 0)
					ff[i&1][f] = (1 + ff[(i+1)&1][f+1] + ff[(i+1)&1][f]) % MOD;
				else
					ff[i&1][f] = ff[(i+1)&1][f];
		printf("%d\n", ff[0][1]);
	}
	return 0;
}
