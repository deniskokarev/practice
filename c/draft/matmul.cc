/**
 * Matrix multiplication optimization
 */
#include "matmul.hh"

using namespace mm;

static uint64_t multCost(const Mat &m1, const Mat &m2) {
	if (m1.c != m2.r)
		throw(std::invalid_argument("Number of rows in 1st mat must match number of columns in the 2nd"));
	return m1.r*m1.c*m2.c;
}

mm::MultPlan::MultPlan():
	Mat(-1,-1),
	i(-1),
	j(-1),
	li(-1),
	lj(-1),
	ri(-1),
	rj(-1),
	cost(0)
{
}

mm::MultPlan::MultPlan(const Mat &m, int pos):
	Mat(m),
	i(pos),
	j(pos),
	li(-1),
	lj(-1),
	ri(-1),
	rj(-1),
	cost(1)
{
}

mm::MultPlan::MultPlan(int ai, int aj, const MultPlan &l, const MultPlan &r):
	Mat(l.r,r.c),
	i(ai),
	j(aj),
	li(l.i),
	lj(l.j),
	ri(r.i),
	rj(r.j),
	cost(multCost(l, r)*l.cost*r.cost)
{
}

std::pair<int,int> mm::optimalMulPlan(const std::vector<Mat>::iterator &begin,
								  const std::vector<Mat>::iterator &end,
								  std::vector<std::vector<MultPlan>> &result)
{
	auto sz = end-begin;
	result.resize(sz);
	for (auto &v:result)
		v.resize(sz);
	int i=0;
	for (auto it=begin; it!=end; ++it) {
		result[i][i] = MultPlan(*it, i);
		i++;
	}
	for (int k=1; k<sz-1; k++) {
		for (int i=0; i<sz; i++) {
			if (i+k<sz) {
				MultPlan &pleft = result[i][i+k-1]; 
				MultPlan &pdown = result[i+1][i+k];
				MultPlan &p1 = result[i][i]; 
				MultPlan &p2 = result[i+k][i+k];
				if (multCost(p1, pdown) < multCost(pleft, p2))
					result[i][i+k] = MultPlan(i, i+k, p1, pdown);
				else
					result[i][i+k] = MultPlan(i, i+k, pleft, p2);
			}
		}
	}
	return std::pair<int,int>(0, sz-1);
}
