/* ACMP 533 */
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

struct P : public pair<int64_t,int64_t> {
	int64_t &x, &y;
	P():x(first),y(second) {
	}
	P(const P &b):pair<int64_t,int64_t>(b),x(first),y(second) {
	}
	int64_t len2() const {
		return x*x+y*y;
	}
	P operator-(const P &b) const {
		P r(*this);
		r.x -= b.x;
		r.y -= b.y;
		return r;
	}
	P operator*(int n) const {
		P r(*this);
		r.x *= n;
		r.y *= n;
		return r;
	}
	int64_t cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.x >> p.y;
	int64_t ans = 0;
	for (int i=0; i<n; i++) {
		unordered_map<int64_t, set<P>> dist;
		for (int j=0; j<n; j++) {
			int64_t l2 = (pp[j]-pp[i]).len2();
			auto &ort = dist[l2];
			int cnt = ort.size();
			if (cnt > 0) {
				if (ort.find(pp[j]) != ort.end())
					cnt--;
				ans += cnt;
			}
			ort.insert((pp[i]*2)-pp[j]);
		}
	}
	cout << ans << endl;
	return 0;
}
