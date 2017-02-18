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

mm::MultPlan::MultPlan(std::vector<std::vector<MultPlan>> &ar):
	Mat(-1,-1),
	result(ar),
	i(-1),
	j(-1),
	li(-1),
	lj(-1),
	ri(-1),
	rj(-1),
	cost(std::numeric_limits<decltype(cost)>::max())
{
}

mm::MultPlan::MultPlan(std::vector<std::vector<MultPlan>> &ar, const Mat &m, int pos):
	Mat(m),
	result(ar),
	i(pos),
	j(pos),
	li(-1),
	lj(-1),
	ri(-1),
	rj(-1),
	cost(0)
{
}

mm::MultPlan::MultPlan(std::vector<std::vector<MultPlan>> &ar, int ai, int aj, const MultPlan &l, const MultPlan &r):
	Mat(l.r, r.c),
	result(ar),
	i(ai),
	j(aj),
	li(l.i),
	lj(l.j),
	ri(r.i),
	rj(r.j),
	cost(multCost(l, r)+l.cost+r.cost)
{
}

MultPlan& mm::MultPlan::operator=(const MultPlan &o)
{
	r = o.r;
	c = o.c;
	i = o.i;
	j = o.j;
	li = o.li;
	lj = o.lj;
	ri = o.ri;
	rj = o.rj;
	cost = o.cost;
	return *this;
}

std::pair<int,int> mm::optimalMulPlan(const std::vector<Mat>::iterator &begin,
									  const std::vector<Mat>::iterator &end,
									  std::vector<std::vector<MultPlan>> &result)
{
	auto sz = end-begin;
	result.resize(sz);
	for (auto &v:result)
		v.resize(sz, MultPlan(result));
	int i=0;
	for (auto it=begin; it!=end; ++it) {
		result[i][i] = MultPlan(result, *it, i);
		i++;
	}
	for (int k=1; k<sz; k++) {
		for (int i=0; i<sz-k; i++) {
			MultPlan &bestPlan = result[i][i+k];
			for (int j=0; j<k; j++) {
				MultPlan &pleft = result[i][i+j]; 
				MultPlan &pdown = result[i+j+1][i+k];
				MultPlan r(result, i, k, pleft, pdown);
				if (r.cost < bestPlan.cost)
					bestPlan = r;
			}
		}
	}
	return std::pair<int,int>(0, sz-1);
}
