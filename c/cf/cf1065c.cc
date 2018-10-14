#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1065C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> ac(2e5+1);
	int mnh = INT_MAX;
	for (int i=0; i<n; i++) {
		int h;
		scanf("%d", &h);
		ac[h]++;
		mnh = min(mnh, h);
	}
	for (int i=int(ac.size())-2; i>=0; i--)
		ac[i] += ac[i+1];
	int ans = 0;
	if (ac[mnh+1] > 0) {
		int h = int(ac.size())-1;
		while (h > mnh) {
			int64_t shave = 0;
			while (shave + ac[h] <= k && h > mnh) {
				shave += ac[h];
				h--;
			}
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
