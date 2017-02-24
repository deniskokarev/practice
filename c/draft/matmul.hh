#include <stdexcept>      // std::invalid_argument
#include <vector>

namespace mm {
	struct Mat {
		int r, c;
		Mat(int ar, int ac):r{ar},c{ac}{}
	};
	
	struct MultPlan: public Mat {
		int i, j;
		int li, lj, ri, rj;
		uint64_t cost;
		MultPlan();
		MultPlan(const Mat &m, int pos);
		MultPlan(int ai, int aj, const MultPlan &l, const MultPlan &r);
	};

	std::pair<int,int> optimalMulPlan(const std::vector<Mat>::iterator &begin,
									  const std::vector<Mat>::iterator &end,
									  std::vector<std::vector<MultPlan>> &result);

}
