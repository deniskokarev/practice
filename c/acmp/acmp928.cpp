#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <cassert>
/* ACMP 928 */
using namespace std;

constexpr double INF = 1e9;

static double calc_diag(double x, double y, double w) {
	return sqrt((x-y)*(x-y)+w*w);
}

// band of length len encircling npt points
// we'll store ordered sets of those
// in each node of Fenwick tree!
struct LNPT {
	double len;
	int npt;
	bool operator<(const LNPT &o) const { // sort by (len,npt)
		return len < o.len || (len == o.len && npt < o.npt);
	}
};

static void save_lnpt(vector<set<LNPT>> &fw_lnpt, double len, int npt, int ry) {
	int tot_sz = 0; // DEBUG
	for (int i=ry; i<fw_lnpt.size(); i|=i+1) {
		set<LNPT> &slnpt = fw_lnpt[i];
		auto it = slnpt.upper_bound(LNPT{len,-1});
		if (prev(it)->npt < npt) {
			// we inseert only improved values, but before doing that we shall remove all worst to the right
			//cerr << "save found: [len=" << it->len << ",npt=" << it->npt << "]" << endl;
			for (auto nit=next(it); it!=slnpt.end() && it->npt <= npt; it=nit,nit=next(it)) {
				//cerr << "erasing: [len=" << it->len << ",npt=" << it->npt << "]" << endl;
				slnpt.erase(it);
			}
			slnpt.insert(it, LNPT{len,npt});
			tot_sz += slnpt.size(); // DEBUG
		}
	}
	assert(tot_sz < 100000); // DEBUG
}

static int get_max_npt(const vector<set<LNPT>> &fw_lnpt, double len, int ry) {
	int npt = -1;
	for (int i=ry; i>=0; i=(i&(i+1))-1) {
		const set<LNPT> &slnpt = fw_lnpt[i];
		auto it = slnpt.upper_bound(LNPT{len,INT_MAX});
		//cerr << "found: [len=" << it->len << ",npt=" << it->npt << "]" << endl;
		//cerr << "found prev: [len=" << prev(it)->len << ",npt=" << prev(it)->npt << "]" << endl;
		npt = max(npt, prev(it)->npt);
	}
	return npt;
}

int main(int argc, char **argv) {
	double band_l, w;
	cin >> band_l >> w;
	int n;
	cin >> n;
	vector<double> xx(n); // top alley
	for (auto &x:xx)
		cin >> x;
	int m;
	cin >> m;
	vector<double> yy(m);  // bottom
	for (auto &y:yy)
		cin >> y;
	// using Fenwick tree to store sets
	vector<set<LNPT>> fw_lnpts(m, set<LNPT>({LNPT{-1,-1}, LNPT{INF,INT_MAX}}));
	// walking from right to left to start filling LNPTs to the right
	// LNPTs will be naturally organized by x and we'll use
	// fw tree to make sure we take only LNPTs for greater y
	// among those we'll take max npt for available band len
	int mx_npt = -1;
	for (int x=n-1; x>=0; x--) {
		for (int y=m-1,ry=0; y>=0; y--,ry++) {
			// add first
			double diag = calc_diag(xx[x], yy[y], w);
			double len = xx[x] + yy[y] + diag;
			save_lnpt(fw_lnpts, len, x+y, ry);
			// then find
			double fnd_len_le = band_l + xx[x] + yy[y] - diag; // looking for len less or equal than this
			if (fnd_len_le > 0) {
				int npt = get_max_npt(fw_lnpts, fnd_len_le, ry);
				//cerr << "npt=" << npt << endl;
				mx_npt = max(mx_npt, npt-x-y);
			}
		}
	}
	if (mx_npt >= 0)
		cout << mx_npt+2 << endl;
	else
		cout << 0 << endl;
	return 0;
}
