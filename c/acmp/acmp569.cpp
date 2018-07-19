#include <cstdio>
#include <queue>
#include <cstring>
/* ACMP 569 */
using namespace std;

// person
struct P {
	int i, d;
};

// donors
struct D {
	int i, d;
	bool operator <(const D &b) const {
		return d>b.d; // min heap
	}
};

// recepients
struct R {
	int i, d;
	bool operator <(const R &b) const {
		return d<b.d; // max heap
	}
};

// log
struct L {
	int to;
	int sum;
};

int main(int argc, char **argv) {
	int n, ad;
	scanf("%d%d", &n, &ad);
	P pp[n];
	for (int i=0; i<n; i++) {
		auto &p = pp[i];
		scanf("%d", &p.d);
		p.i = i;
	}
	priority_queue<D> dd;
	priority_queue<R> rr;
	for (auto &p:pp) {
		p.d = ad-p.d;
		if (p.d > 0)
			dd.push(D{p.i, p.d});
		else if (p.d < 0)
			rr.push(R{p.i, p.d});
	}
	L ll[n];
	memset(ll, 0, sizeof(ll));
	while (!dd.empty()) {
		D d = dd.top();
		dd.pop();
		R r = rr.top();
		rr.pop();
		r.d += d.d;
		ll[d.i] = L {r.i+1, d.d};
		if (r.d > 0)
			dd.push(D{r.i, r.d});
		else if (r.d < 0)
			rr.push(R{r.i, r.d});
	}
	for (auto &l:ll)
		printf("%d %d\n", l.to, l.sum);
	return 0;
}
