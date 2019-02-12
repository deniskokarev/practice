#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cinttypes>
/* CodeForces CF1114F problem */
using namespace std;

/**
 * Segment tree to perform "lazy" Increments on all values in the open interval [b, e)
 * Then you can still perofrm Fold over the range
 * Both operations run in O(logN)
 */
template<class ValueType, class IncOp, class FoldOp> class IncFoldSegTree {
	using value_type = ValueType;
	int sz;
	int l2;
	std::vector<value_type> tree; // where we keep values and aggregates (first sz elements are aggreagates)
	std::vector<value_type> lazy; // where we keep lazy updates
	/**
	 * Propagate increments down to a specific element in O(logN)
	 */
	void propagate_inc(int pos) {
		for (int l=l2; l>0; l--) {
			int p = pos >> l;
			IncOp()(lazy[p<<1], lazy[p]);
			IncOp()(lazy[(p<<1)|1], lazy[p]);
			lazy[p] = value_type();
		}
	}

public:
	/**
	 * Create segment tree with given size
	 * Upon creation all values will be zeros
	 * @param _sz - maximum size
	 */
	IncFoldSegTree(int _sz):sz(_sz),l2(floor(log2(sz))),tree(sz+sz),lazy(sz+sz) {
	}

	/**
	 * direct access to element for initialization
	 * must use rebuild() afterwards
	 */
	value_type &operator[](size_t i) {
		return tree[sz+i];
	}
	
	/**
	 * If you touched values directly, you must perform rebuild()
	 */
	void rebuild() {
		for (int i=sz+sz-1; i>1; i-=2)
			tree[i>>1] = FoldOp()(tree[i-1], tree[i]);
	}
	
	/**
	 * Perform "lazy" increment by v on all values in the open interval [b, e)
	 * Runs in O(logN)
	 */ 
	void inc_each(int b, int e, const value_type &v) {
		b += sz;
		e += sz;
		while (b < e) {
			if (b&1)
				IncOp()(lazy[b++], v);
			if (e&1)
				IncOp()(lazy[--e], v);
			b >>= 1;
			e >>= 1;
		}
	}

	/**
	 * Perform interval folding on open-ended [b, e) segment. Runs in O(logN)
	 * At each level we will fold with lazy updates
	 * @param b - begin - first element inclusive
	 * @param e - end - element after last
	 * @return fold(tree[b], fold(tree[b+1], fold(tree[b+2], ... fold(tree[e-2], fold(tree[e-1])...)))
	 */
	value_type operator()(int b, int e) {
		b += sz;
		e += sz;
		propagate_inc(b);
		int level = 0;
		if (e-b > 1) {
			propagate_inc(e-1);
			value_type vb = FoldOp()(tree[b], lazy[b], level);
			b++, e--;
			value_type ve = FoldOp()(tree[e], lazy[e], level);
			while (b < e) {
				level++;
				if (b&1) {
					vb = FoldOp()(FoldOp()(vb, tree[b]), lazy[b], level);
					b++;
				}
				if (e&1) {
					e--;
					ve = FoldOp()(FoldOp()(tree[e], ve), lazy[e], level);
				}
				b >>= 1;
				e >>= 1;
			}
			return FoldOp()(vb, ve);
		} else {
			return FoldOp()(tree[b], lazy[b], level);
		}
	}

};

struct P {
	static constexpr int SZ = 300;
	int p[SZ];
	P() {
		fill(p, p+SZ, 0);
	}
};

struct Inc {
	void operator()(P &me, const P &by) const {
		for (int i=0; i<P::SZ; i++)
			me.p[i] += by.p[i];
	}
};

struct Fold {
	// fold values together
	P operator()(const P &a, const P &b) const {
		P r(a);
		for (int i=0; i<r.SZ; i++)
			r.p[i] += b.p[i];
		return r;
	}
	// fold value, lazy update and lazy update power (level in the tree)
	P operator()(const P &a, const P &lazy, int level) const {
		P r(a);
		for (int i=0; i<r.SZ; i++)
			r.p[i] += lazy.p[i] << level;
		return r;
	}
};

constexpr int MOD = 1e9+7;

unsigned pow_mod(unsigned b, unsigned p) {
	if (p) {
		uint64_t r = pow_mod(b, p/2);
		r *= r;
		r %= MOD;
		if (p&1)
			r *= b;
		r %= MOD;
		return r;
	} else {
		return 1;
	}
}

int totient_mod(const P &p) {
	int64_t phi = 1;
	for (int i=0; i<p.SZ; i++) {
		if (p.p[i]) {
			phi *= pow_mod(i, p.p[i]-1) * (i-1);
			phi %= MOD;
		}
	}
	return phi;
}

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int prime_factors(uint64_t n, uint64_t p[]) {
	int np = 0;
	for (uint64_t i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

P getprimes(int x) {
	P node;
	uint64_t pp[64];
	for (int i=prime_factors(x, pp)-1; i>=0; i--)
		node.p[pp[i]]++;
	return node;
}

static uint64_t dbg_pval(const P &p) {
	int v = 1;
	for (int i=0; i<P::SZ; i++)
		v *= pow_mod(i, p.p[i]);
	return v;
}

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	IncFoldSegTree<P, Inc, Fold> segtree(n);
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		segtree[i] = getprimes(a);
	}
	segtree.rebuild();
	while (q--) {
		char qs[32];
		scanf("%32s", qs);
		int l, r, x;
		switch(qs[0]) {
		case 'T':
			{
				scanf("%d%d", &l, &r);
				l--;
				P res = segtree(l, r);
				//fprintf(stderr, "[%d,%d) prod = %" PRIu64 "\n", l, r, dbg_pval(res));
				printf("%d\n", totient_mod(res));
			}
			break;
		case 'M':
			{
				scanf("%d%d%d", &l, &r, &x);
				l--;
				segtree.inc_each(l, r, getprimes(x));
			}
			break;
		}
	}
	return 0;
}
