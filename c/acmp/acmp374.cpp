/* ACMP 374 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

struct P {
	int64_t x, y;
	int64_t len2() const {
		return x*x + y*y;
	}
	P operator-(const P &b) const {
		P res(*this);
		res.x -= b.x;
		res.y -= b.y;
		return res;
	}
	int64_t cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int sign(int64_t n) {
	return (n>0) - (n<0);
}

// a->b->c turns left = +1, right = -1
int orientation(const P &a, const P &b, const P &c) {
	int64_t cr = (b-a).cross(c-b);
	return sign(cr);
}

// Building positive convex hull using Graham method
vector<P> conv(const vector<P> &pp) {
	assert(pp.size() > 1);
	vector<P> op(pp); // order points left->right (down->up)
	sort(op.begin(), op.end(), [](const P &a, const P &b){return a.x<b.x || (a.x==b.x && a.y<b.y);});
	P &ap = op.front();
	P &bp = op.back();
	P vab = bp-ap;
	vector<P> l, r; // points to left/right from ap->bp line (including ap and bp)
	l.push_back(ap);
	for (int i=1; i<op.size()-1; i++) {
		if (sign(vab.cross(op[i]-ap)) > 0)
			l.push_back(op[i]);
		else
			r.push_back(op[i]);
	}
	r.push_back(bp);
	vector<P> cvr; // right side of the convex hull including helper point and ap and bp
	cvr.push_back(P {ap.x-1, ap.y});
	cvr.push_back(ap);
	cvr.push_back(r.front());
	for (int i=1; i<r.size(); i++) {
		while (cvr.size()>2 && orientation(*(cvr.end()-2), *(cvr.end()-1), r[i]) <= 0)
			cvr.pop_back();
		cvr.push_back(r[i]);
	}
	vector<P> cvl; // left side of the convex hull including helper point and bp and ap
	cvl.push_back(P {bp.x+1, bp.y});
	cvl.push_back(bp);
	cvl.push_back(l.back());
	for (int i=l.size()-1; i>=0; i--) {
		while (cvl.size()>2 && orientation(*(cvl.end()-2), *(cvl.end()-1), l[i]) <= 0)
			cvl.pop_back();
		cvl.push_back(l[i]);
	}
	vector<P> cv; // exclude helper points and ap/bp ends
	cv.insert(cv.end(), cvr.begin()+1, cvr.end()-1);
	cv.insert(cv.end(), cvl.begin()+1, cvl.end()-1);
	return cv;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.x >> p.y;
	double pr = 0;
	auto ch = conv(pp);
	for (int i=0; i<ch.size(); i++) {
		P v = ch[i]-ch[(i+1)%ch.size()];
		pr += sqrt(v.len2());
	}
	cout << fixed << setprecision(1) << pr << endl;
	return 0;
}
