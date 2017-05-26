#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
/* CodeForces http://codeforces.com/group/DE717HedLL/contest/213027/problem/D */
using namespace std;

struct S {
	string s, r;
	uint64_t c;
};

#define dim(X)	(sizeof(X)/sizeof(X[0]))

template<typename T> T ifordered(vector<string> &&s, T yes, T no) {
	auto i = s.cbegin();
	auto j = i+1;
	for (j=i+1; j<s.cend(); ++i,++j)
		if (*i > *j)
			return no;
	return yes;
}

uint64_t mincost(const vector<S> &ss, int b, int e, const string &a, const string &z) {
	uint64_t mn;
	if (a > z) {
		mn = ULLONG_MAX;
	} else if (e-b < 1) {
		mn = 0;
	} else if (e-b < 2) {
		uint64_t c[] = {
			ifordered<uint64_t>({a, ss[b].s, z}, 0, ULLONG_MAX),
			ifordered<uint64_t>({a, ss[b].r, z}, ss[b].c, ULLONG_MAX)
		};
		mn = *min_element(c, c+dim(c));
	} else if (e-b < 3) {
		uint64_t c[] = {
			ifordered<uint64_t>({a, ss[b].s, ss[b+1].s, z}, 0, ULLONG_MAX),
			ifordered<uint64_t>({a, ss[b].s, ss[b+1].r, z}, ss[b+1].c, ULLONG_MAX),
			ifordered<uint64_t>({a, ss[b].r, ss[b+1].s, z}, ss[b].c, ULLONG_MAX),
			ifordered<uint64_t>({a, ss[b].r, ss[b+1].r, z}, ss[b].c+ss[b+1].c, ULLONG_MAX)
		};
		mn = *min_element(c, c+dim(c));
	} else {
		int m = (e-1+b)/2;
		struct R {
			uint64_t c;
			const string b, m, e;
		} d[] = {
			ifordered<R>({a, ss[b].s, ss[m].s, ss[e-1].s, z}, {0, 							ss[b].s, ss[m].s, ss[e-1].s}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].s, ss[m].s, ss[e-1].r, z}, {ss[e-1].c,					ss[b].s, ss[m].s, ss[e-1].r}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].s, ss[m].r, ss[e-1].s, z}, {ss[m].c,						ss[b].s, ss[m].r, ss[e-1].s}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].s, ss[m].r, ss[e-1].r, z}, {ss[m].c+ss[e-1].c, 			ss[b].s, ss[m].r, ss[e-1].r}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].r, ss[m].s, ss[e-1].s, z}, {ss[b].c,						ss[b].r, ss[m].s, ss[e-1].s}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].r, ss[m].s, ss[e-1].r, z}, {ss[b].c+ss[e-1].c,			ss[b].r, ss[m].s, ss[e-1].r}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].r, ss[m].r, ss[e-1].s, z}, {ss[b].c+ss[m].c, 			ss[b].r, ss[m].r, ss[e-1].s}, {ULLONG_MAX}),
			ifordered<R>({a, ss[b].r, ss[m].r, ss[e-1].r, z}, {ss[b].c+ss[m].c+ss[e-1].c,	ss[b].r, ss[m].r, ss[e-1].r}, {ULLONG_MAX})
		};
		uint64_t c[dim(d)];
		for (int i=0; i<dim(d); i++) {
			c[i] = ULLONG_MAX;
			if (d[i].c < ULLONG_MAX) {
				uint64_t l = mincost(ss, b+1, m-1, d[i].b, d[i].m);
				uint64_t r = mincost(ss, m+1, e-1, d[i].m, d[i].e);
				if (l != ULLONG_MAX && r != ULLONG_MAX)
					c[i] = d[i].c + l + r;
			}
		}
		mn = *min_element(c, c+dim(c));
	}
	return mn;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<S> ss(n);
	for (auto &s:ss) {
		cin >> s.c;
	}
	for (auto &s:ss) {
		cin >> s.s;
		s.r = s.s;
		reverse(s.r.begin(), s.r.end());
	}
	const string a = {0};
	const string z = {127};
	int64_t c = mincost(ss, 0, ss.size(), a, z);
	cout << c << endl;
	return 0;
}
