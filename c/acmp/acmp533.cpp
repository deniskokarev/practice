/* ACMP 533 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct P {
	int64_t x, y;
	int64_t len2() const {
		return x*x+y*y;
	}
	P operator-(const P &b) const {
		P r(*this);
		r.x -= b.x;
		r.y -= b.y;
		return r;
	}
	int64_t cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	P pp[n];
	for (auto &p:pp)
		cin >> p.x >> p.y;
	int64_t ans = 0;
	for (int i=0; i<n; i++) {
		unordered_map<int64_t, vector<int>> dist;
		for (int j=0; j<n; j++) {
			int64_t l2 = (pp[j]-pp[i]).len2();
			dist[l2].push_back(j);
		}
		for (auto &pr:dist) {
			const auto vn = pr.second;
			for (int k=0; k<int(vn.size())-1; k++) {
				for (int l=k+1; l<int(vn.size()); l++) {
					P sd1 = pp[vn[l]] - pp[i];
					P sd2 = pp[vn[k]] - pp[i];
					P sd3 = pp[vn[k]] - pp[vn[l]];
					// count equilaterals only once
					bool eqt = (sd1.len2() == sd2.len2() && sd2.len2() == sd3.len2());
					if (sd1.cross(sd2) != 0 && (!eqt || (i<vn[l] && i<vn[k])))
						ans++;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
