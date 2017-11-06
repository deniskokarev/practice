/* ACMP 117 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// rational number
struct Q {
	int64_t n, d;
	Q(int64_t _n, int64_t _d) {
		if (d<0) {
			n = -_n;
			d = -_d;
		} else {
			n = _n;
			d = _d;
		}
	}
	bool operator<(const Q &b) const {
		return n*b.d < b.n*d;
	}
};

int sign(int n) {
	return (n>0) - (n<0);
}

struct UniqP {
	int x, y;
	bool operator<(const UniqP &b) const {
		return x<b.x || (x==b.x && y<b.y);
	}
};

struct P {
	int x, y;
	bool operator<(const P &b) const {
		return x*x+y*y < b.x*b.x+b.y*b.y;
	}
	int cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

// signed sin^2 between a,b and b,c
Q sin2(const P &a, const P &b, const P &c) {
	int x1 = b.x-a.x, y1 = b.y-a.y;
	int x2 = c.x-b.x, y2 = c.y-b.y;
	int lab2 = x1*x1+y1*y1;
	int lbc2 = x2*x2+y2*y2;
	int cr = x1*y2-y1*x2;
	return Q(cr*cr*sign(cr), lab2*lbc2);
}

// a->b->c turns left = +1, right = -1
int orientation(const P &a, const P &b, const P &c) {
	int x1 = b.x-a.x, y1 = b.y-a.y;
	int x2 = c.x-b.x, y2 = c.y-b.y;
	int cr = x1*y2-y1*x2;
	return sign(cr);
}

// Building positive convex hull using Graham method
// All angles are signed sin^2 represented in rational numbers
// for accuracy
vector<P> conv(const vector<P> &pp, int n, int sidx) {
	vector<pair<Q,P>> ordp;
	for (int i=0; i<n; i++) {
		if (i!=sidx)
			ordp.push_back(make_pair(sin2(P{pp[sidx].x-1,pp[sidx].y}, pp[sidx], pp[i]), pp[i]));
	}
	sort(ordp.begin(), ordp.end());
	vector<P> conv;
	conv.push_back(pp[sidx]);
	conv.push_back(ordp[0].second);
	for (int i=1; i<n-1; i++) {
		while (orientation(*(conv.end()-2), *(conv.end()-1), ordp[i].second) < 0)
			conv.pop_back();
		conv.push_back(ordp[i].second);
	}
	return conv;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	set<UniqP> spp;
	for (int i=0; i<n; i++) {
		UniqP p;
		cin >> p.x >> p.y;
		spp.insert(p);
	}
	n = spp.size();
	vector<P> pp(n);
	int sidx = 0; // lower left point
	int i=0;
	for (auto sp:spp) {
		pp[i] = P {sp.x, sp.y};
		if (pp[sidx].x > sp.x || (pp[sidx].x >= sp.x && pp[sidx].y > sp.y))
			sidx = i;
		i++;
	}
	if (n > 2) {
		int64_t s = 0;
		auto ch = conv(pp, n, sidx);
		//for (auto &c:ch)
		//	cerr << "x: " << c.x << " y: " << c.y << endl;
		for (int i=0; i<ch.size()-1; i++)
			s += ch[i].cross(ch[i+1]);
		s += ch.back().cross(ch.front());
		if (s&1)
			cout << s/2+1 << endl;
		else
			cout << s/2 << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
