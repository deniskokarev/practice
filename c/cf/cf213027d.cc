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

uint64_t ifordered(const string **b, const string **e, uint64_t yes, uint64_t no) {
	auto i = b;
	auto j = i+1;
	for (j=i+1; j<e; ++i,++j)
		if (**i > **j)
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
		struct {
			const string *s[3];
			uint64_t c;
		} d[] = {
			{{&a, &ss[b].s, &z}, 0},
			{{&a, &ss[b].r, &z}, ss[b].c}
		};
		uint64_t c[dim(d)];
		for (int i=0; i<dim(d); i++)
			c[i] = ifordered(d[i].s, d[i].s+dim(d[i].s), d[i].c, ULLONG_MAX);
		mn = *min_element(c, c+dim(c));
	} else if (e-b < 3) {
		struct {
			const string *s[4];
			uint64_t c;
		} d[] = {
			{{&a, &ss[b].s, &ss[b+1].s, &z}, 0},
			{{&a, &ss[b].s, &ss[b+1].r, &z}, ss[b+1].c},
			{{&a, &ss[b].r, &ss[b+1].s, &z}, ss[b].c},
			{{&a, &ss[b].r, &ss[b+1].r, &z}, ss[b].c+ss[b+1].c}
		};
		uint64_t c[dim(d)];
		for (int i=0; i<dim(d); i++)
			c[i] = ifordered(d[i].s, d[i].s+dim(d[i].s), d[i].c, ULLONG_MAX);
		mn = *min_element(c, c+dim(c));
	} else {
		int m = (e-1+b)/2;
		struct {
			const string *s[5];
			uint64_t c;
		} d[] = {
			{{&a, &ss[b].s, &ss[m].s, &ss[e-1].s, &z}, 0},
			{{&a, &ss[b].s, &ss[m].s, &ss[e-1].r, &z}, ss[e-1].c},
			{{&a, &ss[b].s, &ss[m].r, &ss[e-1].s, &z}, ss[m].c},
			{{&a, &ss[b].s, &ss[m].r, &ss[e-1].r, &z}, ss[m].c+ss[e-1].c},
			{{&a, &ss[b].r, &ss[m].s, &ss[e-1].s, &z}, ss[b].c},
			{{&a, &ss[b].r, &ss[m].s, &ss[e-1].r, &z}, ss[b].c+ss[e-1].c},
			{{&a, &ss[b].r, &ss[m].r, &ss[e-1].s, &z}, ss[b].c+ss[m].c},
			{{&a, &ss[b].r, &ss[m].r, &ss[e-1].r, &z}, ss[b].c+ss[m].c+ss[e-1].c}
		};
		uint64_t c[dim(d)];
		for (int i=0; i<dim(d); i++) {
			c[i] = ULLONG_MAX;
			uint64_t g = ifordered(d[i].s, d[i].s+dim(d[i].s), d[i].c, ULLONG_MAX);
			if (g < ULLONG_MAX) {
				uint64_t l = mincost(ss, b+1, m-1, *d[i].s[1], *d[i].s[2]);
				if (l != ULLONG_MAX) {
					uint64_t r = mincost(ss, m+1, e-1, *d[i].s[2], *d[i].s[3]);
					if (r != ULLONG_MAX) {
						c[i] = g + l + r;
					}
				}
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
