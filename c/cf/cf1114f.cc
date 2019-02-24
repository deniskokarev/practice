#include <cstdio>
#include <vector>
#include <cmath>
#include <bitset>
/* CodeForces CF1114F problem */
using namespace std;

/**
 * Segment tree to perform "lazy" Increments on all values in the open interval [b, e)
 * Then you can still perofrm Fold over the range. FoldOp must be supporting 2 operations:
 *    fold two ValueTypes and fold ValueType with LazyType and level
 * LazyTypes must support += between them
 * All operations run in O(logN)
 */
template<class ValueType, class LazyType, class FoldOp> class LazySegTree {
	using value_type = ValueType;
	using lazy_type = LazyType;
	int sz;
	int l2;
	std::vector<value_type> tree; // where we keep all values (first sz elements are aggreagates)
	std::vector<lazy_type> lazy;

	void rebuild_pos(int p) {
		int level = 1;
		while (p > 1) {
			p >>= 1;
			int c1 = p << 1;
			int c2 = c1 + 1;
			tree[p] = FoldOp()(FoldOp()(tree[c1], tree[c2]), lazy[p], level);
			level++;
		}
	}

	/**
	 * Propagate increments down to a specific element in O(logN)
	 */
	void propagate_inc(int pos) {
		for (int l=l2; l>0; l--) {
			int p = pos >> l;
			int c1 = p << 1;
			int c2 = c1 + 1;
			lazy[c1] += lazy[p];
			lazy[c2] += lazy[p];
			tree[c1] = FoldOp()(tree[c1], lazy[p], l-1);
			tree[c2] = FoldOp()(tree[c2], lazy[p], l-1);
			lazy[p] = lazy_type();
		}
	}
public:
	/**
	 * Create lazy segment tree with given size
	 * Upon creation all values will be zeros
	 * @param sz - maximum size
	 */
	LazySegTree(int _sz):sz(_sz),l2(floor(log2(sz))),tree(sz+sz),lazy(sz+sz) {
	}

	value_type &operator[](int p) {
		return tree[p+sz];
	}
	
	void rebuild() {
		for (int i=sz+sz-1; i>1; i-=2)
			tree[i>>1] = FoldOp()(tree[i-1], tree[i]);
	}

	/**
	 * Perform "lazy" increment by v on all values in the open interval [b, e)
	 * Runs in O(logN)
	 */ 
	void inc(int b, int e, const lazy_type &v) {
		b += sz;
		e += sz;
		int rb = b;
		int re = e;
		int level = 0;
		while (b < e) {
			if (b&1) {
				tree[b] = FoldOp()(tree[b], v, level);
				lazy[b] += v;
				b++;
			}
			if (e&1) {
				--e;
				tree[e] = FoldOp()(tree[e], v, level);
				lazy[e] += v;
			}
			b >>= 1;
			e >>= 1;
			level++;
		}
		rebuild_pos(rb);
		rebuild_pos(re-1);
	}

	/**
	 * Perform interval folding on open-ended [b, e) segment. Runs in O(logN)
	 * Folding is left-associative
	 * @param b - begin - first element inclusive
	 * @param e - end - element after last
	 * @return fold(tree[b], fold(tree[b+1], fold(tree[b+2], ... fold(tree[e-2], fold(tree[e-1])...)))
	 */
	value_type operator()(int b, int e) {
		b += sz;
		e += sz;
		propagate_inc(b);
		if (e-b > 1) {	
			value_type vb = value_type();
			value_type ve = value_type();
			propagate_inc(e-1);
			while (b < e) {
				if (b&1)
					vb = FoldOp()(vb, tree[b++]);
				if (e&1)
					ve = FoldOp()(tree[--e], ve);
				b >>= 1;
				e >>= 1;
			}
			return FoldOp()(vb, ve);
		} else if (e-b == 1) {
			return tree[b];
		} else {
			return value_type();
		}
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

/**
 * Precompute inverted primes in ring modulo MOD
 * 0 for non-primes
 */
template<int MXSZ> class InvPrimes {
	int inv_primes[MXSZ];
public:
	InvPrimes() {
		fill(inv_primes, inv_primes+MXSZ, 1);
		for (int i=2; i<MXSZ; i++)
			for (int j=i+i; j<MXSZ; j+=i)
				inv_primes[j] = 0;
		inv_primes[0] = 0;
		inv_primes[1] = 1;
		for (int i=2; i<MXSZ; i++)
			if (inv_primes[i])
				inv_primes[i] = pow_mod(i, MOD-2);
	}
	const int &operator[](int i) const {
		return inv_primes[i];
	}
};

/**
 * In order to compute the totient of the product
 * we may keep only product and the list of primes
 * involved. No need to keep prime powers
 * We'll keep P() elements in the nodes of segment tree
 */
class P {
	static constexpr int SZ = 300;
	static const InvPrimes<P::SZ> inv_primes;
	int prod;
	bitset<SZ> primes;
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
public:
	P():prod(1),primes(0) {
	}
	P(int x):prod(x),primes(0) {
		uint64_t pp[64];
		for (int i=prime_factors(x, pp)-1; i>=0; i--)
			primes[pp[i]] = 1;
	}
	void operator+=(const P &o) {
		int64_t rp(prod);
		rp *= o.prod;
		rp %= MOD;
		prod = int(rp);
		primes |= o.primes;
	}
	P pow(int pow) const {
		P res(*this);
		res.prod = pow_mod(prod, pow);
		return res;
	}
	int totient() const {
		int64_t phi = prod;
		for (int i=0; i<P::SZ; i++) {
			if (primes[i]) {
				phi *= (i-1);
				phi %= MOD;
				phi *= inv_primes[i];
				phi %= MOD;
			}
		}
		return int(phi);
	}
};

const InvPrimes<P::SZ> P::inv_primes;

/**
 * Our lazy segtree update operations
 */
struct Fold {
	P mul(const P &a, const P &b) const {
		P res(a);
		res += b;
		return res;
	}
	// "combine" 2 values together
	P operator()(const P &a, const P &b) const {
		return mul(a, b);
	}
	// "combine" value with lazy update value and its power (level of the lazy update in the tree)
	P operator()(const P &a, const P &lazy, int level) const {
		return mul(a, lazy.pow(1<<level));
	}
};

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	LazySegTree<P, P, Fold> segtree(n);
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		segtree[i] = P(a);
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
				//fprintf(stderr, "[%d,%d) prod = %d\n", l, r, res.prod);
				printf("%d\n", res.totient());
			}
			break;
		case 'M':
			{
				scanf("%d%d%d", &l, &r, &x);
				l--;
				segtree.inc(l, r, P(x));
			}
			break;
		}
	}
	return 0;
}
