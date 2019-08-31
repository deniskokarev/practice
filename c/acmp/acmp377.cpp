#include <cstdio>
#include <vector>
#include <algorithm>
/* ACMP 377 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<pair<int,int>> pp(n*2);
	for (int i=0; i<n; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		pp[i*2] = make_pair(l, -1);
		pp[i*2+1] = make_pair(r, +1);
	}
	sort(pp.begin(), pp.end());
	int h = 0;
	int l = -1;
	int ans = 0;
	for (auto &p:pp) {
		if (h == 0 && p.second == -1)
			l = p.first;
		if (h == -1 && p.second == 1)
			ans += p.first-l;
		h += p.second;
	}
	printf("%d\n", ans);
	return 0;
}
