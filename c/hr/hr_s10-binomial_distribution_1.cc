#include <iostream>
#include <iomanip>
#include <vector>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-binomial-distribution-1 */
using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

struct CP {
	int color;
	int p;
};

void calc_r(uint64_t *sm_all, uint64_t *sm_sel, const vector<vector<CP>> &cp, int lvl, uint64_t p, int c) {
	if (lvl < cp.size()) {
		for (auto &el:cp[lvl])
			calc_r(sm_all, sm_sel, cp, lvl+1, p*el.p, c+el.color);
	} else {
		*sm_all += p;
		if (c > 2)
			*sm_sel += p;
	}
}

int main(int argc, char **argv) {
	vector<vector<CP>> cp {{{0, 100}, {1, 109}}, {{0, 100}, {1, 109}}, {{0, 100}, {1, 109}}, {{0, 100}, {1, 109}}, {{0, 100}, {1, 109}}, {{0, 100}, {1, 109}}};
	uint64_t sm_all = 0;
	uint64_t sm_sel = 0;
	calc_r(&sm_all, &sm_sel, cp, 0, 1, 0);
	int g = gcd(sm_sel, sm_all);
	sm_sel /= g;
	sm_all /= g;
	cout << fixed << setprecision(3) << (long double)(sm_sel) / sm_all << endl;
	return 0;
}
