#include <cstdio>
#include <cinttypes>
#include <set>
/* Hackerrank https://www.hackerrank.com/challenges/subsequence-weighting */
using namespace std;

struct P {
	int h;
	int64_t w;
	bool operator<(const P &b) const {
		return h<b.h || (h==b.h && w<b.w);
	}
};

int64_t solve(const P *pp, int sz) {
	set<P> h2s;
	h2s.insert(P {0, 0});
	for (int i=0; i<sz; i++) {
		const P &p = pp[i];
		auto fnd = h2s.lower_bound(P {p.h, 0});
		int64_t ns = prev(fnd)->w + p.w;
		while (fnd != h2s.end() && fnd->w <= ns) {
			auto fn = next(fnd);
			h2s.erase(fnd);
			fnd = fn;
		}
		h2s.insert(P {p.h, ns});
	}
	return h2s.rbegin()->w;
}

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		P pp[n];
		for (auto &p:pp)
			scanf("%d", &p.h);
		for (auto &p:pp)
			scanf("%" PRId64, &p.w);
		printf("%" PRId64 "\n", solve(pp, n));
	}
}
