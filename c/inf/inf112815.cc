#include <iostream>
#include <array>
#include <vector>
/* ROI 2015A */

using P = std::array<int, 3>; // person

// map of totals
struct MAP {
	int sz;
	std::vector<int> a;	// level
	std::vector<std::vector<int>> ab; // column on the level
	std::vector<std::vector<int>> ac; // row on the level
	std::vector<std::vector<std::vector<int>>> abc; // cell
	MAP(int sz):
		sz(sz),
		a(sz),
		ab(sz, std::vector<int>(sz)),
		ac(sz, std::vector<int>(sz)),
		abc(sz, std::vector<std::vector<int>>(sz, std::vector<int>(sz)))
	{}
};

// map people to hypercube of their characteristics with totals
// adim - is a dimention we consider first
const MAP map_people(const std::vector<P> &ppl, int adim, int sz) {
	MAP m(sz);
	int i = adim; // first
	int j = (i+1)%3; // second
	int k = (j+1)%3; // and third dimentions
	for (auto &p:ppl) {
		m.a[p[i]]++;
		m.ab[p[i]][p[j]]++;
		m.ac[p[i]][p[k]]++;
		m.abc[p[i]][p[j]][p[k]]++;
	}
	return m;
}

// count pairs with equal first dimention and
// at the same time different second and third dims
int64_t cnt_pairs(const MAP &m, int sz) {
	int64_t s = 0;
	for (int i=0; i<sz; i++)
		for (int j=0; j<sz; j++)
			for (int k=0; k<sz; k++)
				s += int64_t(m.abc[i][j][k])*(m.a[i]-m.ab[i][j]-m.ac[i][k]+m.abc[i][j][k]);
	return s/2; // uniq pairs
}

constexpr int SZ = 101; // max characteristic value

int main(int argc, char **argv) {
	int n;
	std::cin >> n;
	std::vector<P> ppl(n);
	for (auto &p:ppl)
		std::cin >> p[0] >> p[1] >> p[2];
	int64_t ans = 0;
	for (int dim=0; dim<3; dim++) // for each eq dimention
		ans += cnt_pairs(map_people(ppl, dim, SZ), SZ);
	std::cout << ans << std::endl;
	return 0;
}
