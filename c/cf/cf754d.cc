#include <iostream>
#include <algorithm>
/* CodeForces CF754D problem */
using namespace std;

struct C {
	int64_t l, r;
};

struct CS {
	int64_t pos;
	int sign;
	int id;
};

int fill_ccs(CS *ccs, int n, int64_t shrink, C *cc) {
	int len=0;
	for (int i=0; i<n; i++) {
		auto &c = cc[i];
		if (c.r > c.l+shrink) {
			ccs[len++] = CS {c.l, +1, i};
			ccs[len++] = CS {c.r-shrink, -1, i};
		}
	}
	sort(ccs, ccs+len, [](const CS &a, const CS &b){return a.pos<b.pos || (a.pos==b.pos && a.sign<b.sign);});
	return len;
}

int count_overlaps(int n, int64_t shrink, C *cc) {
	CS ccs[n+n];
	int len = fill_ccs(ccs, n, shrink, cc);
	int cnt = 0;
	int mx = 0;
	for (int i=0; i<len; i++) {
		cnt += ccs[i].sign;
		mx = max(cnt, mx);
	}
	return mx;
}

void select_coupons(int n, int64_t shrink, C *cc, int *sel, int mx) {
	CS ccs[n+n];
	int len = fill_ccs(ccs, n, shrink, cc);
	int cnt = 0;
	for (int i=0; i<len; i++) {
		cnt += ccs[i].sign;
		sel[ccs[i].id] += ccs[i].sign;
		if (cnt == mx)
			break;
	}
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	C cc[n];
	for (auto &c:cc) {
		cin >> c.l >> c.r;
		c.r++;
	}
	sort(cc, cc+n, [](const C &a, const C &b){return a.l<b.l;});
	int64_t f=0, t=LONG_MAX;
	int cnt;
	while (f<t) {
		int64_t m = f+(t-f)/2;
		cnt = count_overlaps(n, m, cc);
		if (cnt < k)
			t = m;
		else
			f = m+1;
	}
	int shrink = f;
	cout << shrink << endl;
	if (shrink > 0) {
		int sel[n];
		fill(sel, sel+n, 0);
		select_coupons(n, shrink-1, cc, sel, cnt);
		for (int i=0; i<n; i++)
			if (sel[i]>0)
				cout << i+1 << ' ';
	} else {
		for (int i=0; i<k; i++)
			cout << i+1 << ' ';
	}
	cout << endl;
	return 0;
}
