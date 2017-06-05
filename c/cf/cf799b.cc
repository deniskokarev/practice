#include <iostream>
#include <algorithm>

#define dim(X)	((int)(sizeof(X)/sizeof(X[0])))

/* CodeForces http://codeforces.com/problemset/problem/799/B */
using namespace std;

struct T {
	struct T *nt[4], *pv[4];
	int price;
	int ca, cb;
};

void advance(T *t) {
	T *na = t->nt[t->ca];
	T *pa = t->pv[t->ca];
	T *nb = t->nt[t->cb];
	T *pb = t->pv[t->cb];
	if (t->pv[t->ca])
		t->pv[t->ca]->nt[t->ca] = na;
	if (t->pv[t->cb])
		t->pv[t->cb]->nt[t->cb] = nb;
	if (na)
		na->pv[t->ca] = pa;
	if (nb)
		nb->pv[t->cb] = pb;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	T tt[n];
	for (auto &t:tt)
		cin >> t.price;
	for (auto &t:tt)
		cin >> t.ca;
	for (auto &t:tt)
		cin >> t.cb;
	for (auto &t:tt) {
		fill(t.nt, t.nt+dim(t.nt), nullptr);
		fill(t.pv, t.pv+dim(t.pv), nullptr);
	}
	int m;
	cin >> m;
	int cc[m];
	for (auto &c:cc)
		cin >> c;
	sort(tt, tt+n, [](const T &a, const T &b){return a.price < b.price;});
	T *nt[4] = {nullptr, nullptr, nullptr, nullptr};
	for (int i=n-1; i>=0; i--) {
		T &t = tt[i];
		t.nt[t.ca] = nt[t.ca];
		t.nt[t.cb] = nt[t.cb];
		nt[t.ca] = &t;
		nt[t.cb] = &t;
	}
	T *pv[4] = {nullptr, nullptr, nullptr, nullptr};
	for (int i=0; i<n; i++) {
		T &t = tt[i];
		t.pv[t.ca] = pv[t.ca];
		t.pv[t.cb] = pv[t.cb];
		pv[t.ca] = &t;
		pv[t.cb] = &t;
	}
	T h = {.nt = {nt[0], nt[1], nt[2], nt[3]}};
	for (int c=0; c<dim(h.nt); c++)
		if (nt[c])
			nt[c]->pv[c] = &h;
	for (auto &c:cc) {
		T *t = h.nt[c];
		if (t) {
			cout << t->price;
			advance(t);
		} else {
			cout << -1;
		}
		cout << ' ';
	}
	cout << endl;
	return 0;
}
