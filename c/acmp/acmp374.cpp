/* ACMP 374 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <cstdio>

using namespace std;

int sign(int64_t n) {
	return (n>0) - (n<0);
}

struct P {
	int64_t x, y;
	bool operator==(const P &b) const {
		return x==b.x && y == b.y;
	}
	bool operator<(const P &b) const {
		return x*x+y*y < b.x*b.x+b.y*b.y;
	}
	int64_t len2() const {
		return x*x + y*y;
	}
	P operator-(const P &b) const {
		P res(*this);
		res.x -= b.x;
		res.y -= b.y;
		return res;
	}
};

// signed sin^2 between a,b and b,c
double sin2(const P &a, const P &b, const P &c) {
	int64_t x1 = b.x-a.x, y1 = b.y-a.y;
	int64_t x2 = c.x-b.x, y2 = c.y-b.y;
	double lab2 = x1*x1+y1*y1;
	double lbc2 = x2*x2+y2*y2;
	double cr = x1*y2-y1*x2;
	return cr/lab2/lbc2;
}

// a->b->c turns left = +1, right = -1
int orientation(const P &a, const P &b, const P &c) {
	int64_t x1 = b.x-a.x, y1 = b.y-a.y;
	int64_t x2 = c.x-b.x, y2 = c.y-b.y;
	int64_t cr = x1*y2-y1*x2;
	return sign(cr);
}

// Building positive convex hull using Graham method
// All angles are signed sin^2 in rational numbers
// for accuracy
vector<P> conv(const vector<P> &pp) {
	assert(pp.size() > 1);
	int sidx = 0;
	int i = 0;
	for (auto &p:pp) {
		if (pp[sidx].x > p.x || (pp[sidx].x >= p.x && pp[sidx].y > p.y))
			sidx = i;
		i++;
	}
	vector<pair<double,P>> ordp;
	for (int i=0; i<pp.size(); i++) {
		if (i!=sidx)
			ordp.push_back(make_pair(sin2(P{pp[sidx].x-1,pp[sidx].y}, pp[sidx], pp[i]), pp[i]));
	}
	sort(ordp.begin(), ordp.end());
	vector<P> conv;
	conv.push_back(pp[sidx]);
	conv.push_back(ordp[0].second);
	for (int i=1; i<ordp.size(); i++) {
		while (orientation(*(conv.end()-2), *(conv.end()-1), ordp[i].second) < 0)
			conv.pop_back();
		conv.push_back(ordp[i].second);
	}
	return conv;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.x >> p.y;
	if (pp.size() > 1) {
		double pr = 0;
		auto ch = conv(pp);
		for (int i=0; i<ch.size(); i++) {
			P v = ch[i]-ch[(i+1)%ch.size()];
			pr += sqrt(v.len2());
		}
		printf("%.2f\n", pr);
	} else {
		cout << 0 << endl;
	}
	return 0;
}
