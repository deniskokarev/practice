#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
/* ICPC https://judge.icpc.global/problems/azulejos */
using namespace std;

struct T {
	int p;
	int h;
	int id;
	bool operator<(const T &o) const {
		return h<o.h;
	}
	bool operator>(const T &o) const {
		return h>o.h;
	}
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	// back
	vector<T> bb(n);
	for (int i=0; i<n; i++)
		bb[i].id = i;
	for (auto &b:bb)
		scanf("%d", &b.p);
	for (auto &b:bb)
		scanf("%d", &b.h);
	map<int,multiset<T,std::less<T>>> bm; // price(1) -> T(*)
	for (auto &b:bb)
		bm[b.p].insert(b);
	// front
	vector<T> ff(n);
	for (int i=0; i<n; i++)
		ff[i].id = i;
	for (auto &f:ff)
		scanf("%d", &f.p);
	for (auto &f:ff)
		scanf("%d", &f.h);
	map<int,multiset<T,std::greater<T>>> fm; // price(1) -> T(*)
	for (auto &f:ff)
		fm[f.p].insert(f);
	// merge
	auto f = fm.begin();
	auto b = bm.begin();
	vector<T> bo;
	vector<T> fo;
	while (f != fm.end() && b != bm.end()) {
		int fsz = f->second.size();
		int bsz = b->second.size();
		if (fsz < bsz) {
			for (auto &fn:f->second) {
				auto bfnd = b->second.upper_bound(fn);
				if (bfnd != b->second.end()) {
					fo.push_back(fn);
					bo.push_back(*bfnd);
					//fprintf(stderr, "[%d,%d]->[%d,%d]\n", bfnd->p, bfnd->h, fn.p, fn.h);
					b->second.erase(bfnd);
				} else {
					goto end;
				}
			}
			f = next(f);
		} else {
			for (auto &bn:b->second) {
				auto ffnd = f->second.upper_bound(bn);
				if (ffnd != f->second.end()) {
					fo.push_back(*ffnd);
					bo.push_back(bn);
					//fprintf(stderr, "[%d,%d]->[%d,%d]\n", bn.p, bn.h, ffnd->p, ffnd->h);
					f->second.erase(ffnd);
				} else {
					goto end;
				}
			}
			b = next(b);
			if (fsz == bsz)
				f = next(f);
		}
	}
 end:
	if (bo.size() == n) {
		for (int i=0; i<n; i++)
			printf("%d ", bo[i].id+1);
		printf("\n");
		for (int i=0; i<n; i++)
			printf("%d ", fo[i].id+1);
		printf("\n");
	} else {
		printf("impossible\n");
	}
	return 0;
}
