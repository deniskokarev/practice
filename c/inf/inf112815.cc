#include <iostream>
#include <array>
#include <vector>
/* ROI 2015A */
using namespace std;

struct M {
	int sz;
	vector<int> a;	// level
	vector<vector<int>> ab;	// column on the level
	vector<vector<int>> ac; // row on the level
	vector<vector<vector<int>>> abc; // cell
	M(int sz):
		sz(sz),
		a(sz),
		ab(sz, vector<int>(sz)),
		ac(sz, vector<int>(sz)),
		abc(sz, vector<vector<int>>(sz, vector<int>(sz)))
	{}
};

// map people to hypercube of their characteristics
// adim - is a dimention we consider first
M map_people(vector<array<int,3>> pp, int adim, int sz) {
	M map(sz);
	int i = adim; // first
	int j = (i+1)%3; // second
	int k = (j+1)%3; // and third dimentions
	for (auto &p:pp) {
		map.a[p[i]]++;
		map.ab[p[i]][p[j]]++;
		map.ac[p[i]][p[k]]++;
		map.abc[p[i]][p[j]][p[k]]++;
	}
	return map;
}

// count pairs with all first euqal first dimention and
// at the same time both other dimentions are not eq
int64_t cnt_pairs(const M &map, int sz) {
	int64_t s = 0;
	for (int i=0; i<sz; i++)
		for (int j=0; j<sz; j++)
			for (int k=0; k<sz; k++)
				s += int64_t(map.abc[i][j][k])*(map.a[i]-map.ab[i][j]-map.ac[i][k]+map.abc[i][j][k]);
	return s/2; // uniq pairs
}

constexpr int SZ = 101;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<array<int,3>> pp(n);
	for (auto &p:pp)
		cin >> p[0] >> p[1] >> p[2];
	int64_t ans = 0;
	for (int dim=0; dim<3; dim++)
		ans += cnt_pairs(map_people(pp, dim, SZ), SZ);
	cout << ans << endl;
	return 0;
}
