/* ACMP 533 */
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct P : public pair<int,int> {
	int &x, &y;
	P():x(first),y(second) {
	}
	P(const P &b):pair<int,int>(b),x(first),y(second) {
	}
	int64_t len2() const {
		return int64_t(x)*x+int64_t(y)*y;
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
};

// don't need to worry about equilateral triangles, as we're on integer grid
int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.x >> p.y;
	int64_t ans = 0;
	for (int i=0; i<n; i++) {
		// length^2 -> opposite points (to exclude degenerate trianges)
		map<int64_t, set<P>> dist;
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
