#include <stdexcept>      // std::invalid_argument
#include <vector>
		
namespace mm {
	struct Mat {
		int r, c;
		Mat(int ar, int ac):r{ar},c{ac}{}
	};

	struct MultPlan: public Mat {
		std::vector<std::vector<MultPlan>> &result;
		int i, j;
		int li, lj, ri, rj;
		uint64_t cost;
		MultPlan(std::vector<std::vector<MultPlan>> &result);
		MultPlan(std::vector<std::vector<MultPlan>> &result, const Mat &m, int pos);
		MultPlan(std::vector<std::vector<MultPlan>> &result, int ai, int aj, const MultPlan &l, const MultPlan &r);
		MultPlan &operator=(const MultPlan &o);
	};

	std::pair<int,int> optimalMulPlan(const std::vector<Mat>::iterator &begin,
									  const std::vector<Mat>::iterator &end,
									  std::vector<std::vector<MultPlan>> &result);
}
