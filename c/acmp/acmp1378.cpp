/* ACMP 1378 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

struct E {
	int f, tf, t, tt;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int a, b;
	scanf("%d%d", &a, &b);
	int k;
	scanf("%d", &k);
	E ee[k];
	for (auto &e:ee)
		scanf("%d%d%d%d", &e.f, &e.tf, &e.t, &e.tt);
	int dd[n+1];
	fill(dd, dd+n+1, DINF);
	dd[a] = 0;
	// simple ford, no loop detection needed
	bool doford = true;
	while (doford) {
		doford = false;
		for (const auto &e:ee) {
			if (dd[e.f] <= e.tf && e.tt < dd[e.t]) {
				dd[e.t] = e.tt;
				doford = true;
			}
		}
	}
	printf("%d\n", dd[b]);
	return 0;
}
