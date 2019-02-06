#include <iostream>
#include <vector>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-mcq-3 */
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

void calc_r(int *sm_all, int *sm_sel, const vector<vector<CP>> &cp, int lvl, int p, int c) {
	if (lvl < cp.size()) {
		for (auto &el:cp[lvl])
			calc_r(sm_all, sm_sel, cp, lvl+1, p*el.p, c+el.color);
	} else {
		*sm_all += p;
		if (c == 1)
			*sm_sel += p;
	}
}

int main(int argc, char **argv) {
	vector<vector<CP>> cp {{{0, 5}, {1, 4}}, {{0, 4}, {1, 3}}, {{0, 1}, {1, 1}}};
	int sm_all = 0;
	int sm_sel = 0;
	calc_r(&sm_all, &sm_sel, cp, 0, 1, 0);
	int g = gcd(sm_sel, sm_all);
	printf("%d / %d\n", sm_sel/g, sm_all/g);
	return 0;
}
