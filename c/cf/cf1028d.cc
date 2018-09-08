#include <cstdio>
#include <climits>
#include <set>
/* CodeForces CF1028D problem */
using namespace std;

constexpr unsigned mod = 1e9+7;

int main(int argc, char **argv) {
	set<unsigned> mm;
	int n;
	scanf("%d", &n);
	unsigned s = INT_MAX;
	unsigned b = 0;
	unsigned ans = 1;
	mm.insert(s);
	mm.insert(b);
	for (int i=0; i<n; i++) {
		char op[32];
		int p;
		scanf(" %s%d", op, &p);
		if (op[1] == 'D') {
			// ADD
			mm.insert(p);
		} else {
			// ACCEPT
			if (p > b) {
				if (p < s) {
					ans *= 2;
					ans %= mod;
					auto it = mm.lower_bound(p);
					s = *next(it);
					b = *prev(it);
					mm.erase(it);
				} else if (p > s) {
					ans = 0;
				}
			} else if (p < b) {
				ans = 0;
			}
		}
	}
	printf("%u\n", ans);
	return 0;
}
