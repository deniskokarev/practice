#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-binomial-distribution-2 */

struct CP {
	int color;
	double p;
};

template <class FLT> void calc_r(double *sm_all, double *sm_sel, const std::vector<std::vector<CP>> &cp, int lvl, double p, int c, FLT flt) {
	if (lvl < cp.size()) {
		for (auto &el:cp[lvl])
			calc_r(sm_all, sm_sel, cp, lvl+1, p*el.p, c+el.color, flt);
	} else {
		*sm_all += p;
		if (flt(c))
			*sm_sel += p;
	}
}

int main(int argc, char **argv) {
	std::vector<std::vector<CP>> cp(10, std::vector<CP>{{0, 22}, {1, 3}});
	double sm_all = 0;
	double sm_sel = 0;
	calc_r(&sm_all, &sm_sel, cp, 0, 1, 0, std::bind(std::less<int>(), std::placeholders::_1, 3)); // c < 3
	std::cout << std::fixed << std::setprecision(3) << sm_sel/sm_all << std::endl;
	sm_all = sm_sel = 0;
	calc_r(&sm_all, &sm_sel, cp, 0, 1, 0, std::bind(std::greater<int>(), std::placeholders::_1, 1)); // c > 1
	std::cout << std::fixed << std::setprecision(3) << sm_sel/sm_all << std::endl;
	return 0;
}
