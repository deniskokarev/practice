#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
/* Hakerrank https://www.hackerrank.com/challenges/palindromic-subsets */

using namespace std;

constexpr int MOD = 1e9+7;

struct N {
	static constexpr int L = 26;
	int ofs;
	int ch[L];
	N():ofs(0) {
		std::fill(ch, ch+L, 0);
	}
	N(const char c):N() {
		ch[c%N::L]++;
	}
	// DEBUG
	void dprn() const {
		for (int i=0; i<N::L; i++)
			fprintf(stderr, "%02d ", ch[(i+ofs)%N::L]);
		fprintf(stderr, "\n");
	}
};

void operator+=(N &a, int o) {
	a.ofs = (a.ofs + o) % N::L;
}

void operator+=(N &a, const N &b) {
	for (int i=0; i<N::L; i++)
		a.ch[i] += b.ch[(i+b.ofs-a.ofs+N::L) % N::L];
}

void rebuild(vector<N> &tree, int sz) {
	for (int i=sz+sz-1; i>1; i-=2) {
		tree[i>>1] = tree[i-1];
		tree[i>>1] += tree[i];
	}
}

void shift_range(vector<N> &tree, int sz, int b, int e, int v) {
	b += sz;
	e += sz;
	while (b < e) {
		if (b&1)
			tree[b++] += v;
		if (e&1)
			tree[--e] += v;
		b >>= 1;
		e >>= 1;
	}
}

void propagate_shift(vector<N> &tree, int sz, int l2, int pos) {
	for (int l=l2; l>0; l--) {
		int p = pos >> l;
		tree[p<<1].ofs += tree[p].ofs;
		tree[(p<<1)|1].ofs += tree[p].ofs;
		tree[p] = tree[p<<1];
		tree[p] += tree[(p<<1)|1];
	}
}

N fold(const vector<N> &tree, int sz, int b, int e) {
	b += sz;
	e += sz;
	N v;
	while (b < e) {
		if (b&1)
			v += tree[b++];
		if (e&1)
			v += tree[--e];
		b >>= 1;
		e >>= 1;
	}
	return v;
}

int p2m(int p) {
	if (p == 0)
		return 1;
	int p2 = p2m(p/2);
	p2 *= p2;
	if (p & 1)
		p2 *= 2;
	return p2 % MOD;
}

int ans(const N &res) {
	// two possibilities:
	// 1) one odd others even
	// 2) choosing i-th to be even greater or equal 2
	//    whereas i+1,i+2,... are even too
	pair<int,int64_t> p2[N::L+1];
	int sz = 0;
	for (auto p:res.ch)
		if (p)
			p2[sz++] = make_pair(p, p2m(p-1));
	p2[sz++] = make_pair(0, 1);
	for (int i=sz-2; i>=0; i--) {
		p2[i].second *= p2[i+1].second;
		p2[i].second %= MOD;
	}
	int64_t ans = p2[0].second*(sz-1); // (1)
	ans %= MOD;
	for (int i=0; i<sz-1; i++) { // (2)
		ans += int64_t(p2m(p2[i].first-1)-1) * p2[i+1].second;
		ans %= MOD;
	}
	return int(ans);
}

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	std::vector<N> tree(n+n); // segment tree
	int l2 = int(floor(log2(n))); // tree height
	int i = n;
	int c;
	fgetc(stdin);
	while ((c=fgetc(stdin)) != '\n' && c != EOF && i<n+n)
		tree[i++] = N(c);
	rebuild(tree, n);
	while (q--) {
		int qt;
		int l, r, t; 
		scanf("%d", &qt);
		switch (qt) {
		case 1:
			scanf("%d%d%d", &l, &r, &t);
			shift_range(tree, n, l, r+1, t);
			break;
		case 2:
			scanf("%d%d", &l, &r);
			propagate_shift(tree, n, l2, l);
			propagate_shift(tree, n, l2, r);
			N res = fold(tree, n, l, r+1);
			//res.dprn(); // DEBUG
			printf("%d\n", ans(res));
			break;
		}
	}
	return 0;
}
