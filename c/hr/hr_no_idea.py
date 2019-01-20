#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
/* Hackerrank https://www.hackerrank.com/challenges/white-falcon-and-tree */

/**
 * HLD implementation taken with minor adoption from https://acm.khpnets.info/w/index.php?title=Heavy-light-%D0%B4%D0%B5%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%B7%D0%B8%D1%86%D0%B8%D1%8F
 */
using namespace std;

/**
 * Simple Segment tree on a vector with custom "fold" operation.
 * Supports setting a value at a position and "folding" values on a range
 * Typically, folding would be operator+() or max()
 * O(2*n) space
 * set() - O(n) time
 * fold() - O(n) time
 * @author Denis Kokarev
 */
template<class ValueType=int> struct SegTree {
	using value_type = ValueType;
	using FOLD_OP = std::function<value_type(const value_type &, const value_type &)>;
	int sz;
	std::vector<value_type> tree; // where we keep all values, first sz elements are aggreagates
	std::vector<value_type> lazy; // lazy range set op
	FOLD_OP fold; // "fold" operator to be executed on our interval
	/**
	 * If you touched values directly, you must perform rebuild()
	 */
	void rebuild() {
		for (int i=sz+sz-1; i>1; i-=2)
			tree[i>>1] = fold(tree[i-1], tree[i]);
	}
	void rebuild_pos(int p) {
		while (p > 1) {
			p >>= 1;
			tree[p] = fold();
			tree[p] += tree[p<<1];
			tree[p] += tree[p<<1|1];
			tree[p] [p];
		}
	}
public:
	/**
	 * Create segment tree with given size and custom fold operator
	 * Upon creation all values will be zeros
	 * @param _sz - maximum size
	 * @param _fold	 - custom fold operator - default std::plus
	 */
	SegTree(int _sz, FOLD_OP _fold=std::plus<value_type>()):sz(_sz),tree(sz+sz),fold(_fold) {
	}

	/**
	 * Alternative constructor to initialize the values right away
	 * Works in O(n)
	 * @param list - list of given values
	 * @param _fold	 - custom fold operator - default std::plus
	 */
	SegTree(const std::initializer_list<value_type> &list, FOLD_OP _fold=std::plus<value_type>()):SegTree(list.size(), _fold) {
		std::copy(list.begin(), list.end(), tree.begin()+sz);
		rebuild();
	}
	
	/**
	 * Perform online update in O(logN)
	 * @param pos
	 * @param v
	 */
	void set(int pos, const value_type &v) {
		int node = sz+pos;
		tree[node] = v;
		node >>= 1;
		if (((node<<1)|1) < sz+sz)
			tree[node] = fold(tree[node<<1], tree[(node<<1)|1]);
		else
			tree[node] = tree[node<<1];
		for (node=node>>1; node>0; node >>= 1)
			tree[node] = fold(tree[node<<1], tree[(node<<1)|1]);
	}

	/**
	 * Perform interval folding on open-ended [b, e) segment. Runs in O(logN)
	 * @param b - begin - first element inclusive
	 * @param e - end - element after last
	 * @return fold(tree[b], fold(tree[b+1], fold(tree[b+2], ... fold(tree[e-2], fold(tree[e-1])...)))
	 */
	value_type operator()(int b, int e) const {
		b += sz;
		e += sz;
		if (e-b > 1) {
			value_type vb = tree[b++];
			value_type ve = tree[--e];
			while (b < e) {
				if (b&1)
					vb = fold(vb, tree[b++]);
				if (e&1)
					ve = fold(tree[--e], ve);
				b >>= 1;
				e >>= 1;
			}
			return fold(vb, ve);
		} else {
			return tree[b];
		}
	}
	
	/**
	 * Perform interval folding. Runs in O(logN)
	 * @return fold(tree[b], fold(tree[b+1], fold(tree[b+2], ... fold(tree[e-2], fold(tree[e-1])...)))
	 */
	value_type operator()() const {
		return operator()(0, sz);
	}
};

constexpr int MOD = 1e9+7;

struct F {
	using int64_t = long long;
	int a, b;
	// f1(f2)
	F operator()(const F &f2) const {
		auto na = int64_t(a)*f2.a;
		auto nb = int64_t(a)*f2.b+b;
		return F {int(na % MOD), int(nb % MOD)};
	}
	int operator()(int x) const {
		long long v = x;
		v *= a;
		v += b;
		return v % MOD;
	}
};

// for bidirectional F
struct BF {
	F l, r; // composed as f1(f2(f3)) and f3(f2(f1))
};

struct G {
	int sz;
	vector<vector<int>> ee; // edges
	vector<int> parent;
	vector<int> size; // nodes in subtree
	// node dfs in/out order for ansestry determination
	vector<int> t_in, t_out;
	// what chain and what pos in that chain the node belongs
	vector<int> nchain;
	vector<int> nchpos;
	// chains
	vector<int> chain_root; // root node for the chain
	vector<int> chain_sz;   // number of nodes in the chain
	vector<SegTree<BF>> chain; // chain as segtree
	G(int sz):sz(sz),ee(sz),parent(sz),size(sz),t_in(sz),t_out(sz),nchain(sz),nchpos(sz),chain_root(),chain_sz(),chain(){};
};

int dfs_sizes(G &g, int v, int p, int &tick) {
	g.t_in[v] = tick++;
	g.parent[v] = p;
	g.size[v] = 1;
	for (int c:g.ee[v])
		if (c != p)
			g.size[v] += dfs_sizes(g, c, v, tick);
	g.t_out[v] = tick++;
	return g.size[v];
}

bool not_parent(const G &g, int p, int c) {
	return g.t_in[p] > g.t_in[c] || g.t_out[c] > g.t_out[p];
}

void dfs_hld(G &g, int v, int p, int nchain) {
	g.nchain[v] = nchain;
	g.nchpos[v] = g.chain_sz[nchain];
	g.chain_sz[nchain]++;
	int mxc = -1;
	for (auto c:g.ee[v])
		if (c != p && (mxc == -1 || g.size[c] > g.size[mxc]))
			mxc = c;
	if (mxc != -1) {
		for (auto c:g.ee[v]) {
			if (c != p) {
				if (c != mxc) {
					g.chain_root.push_back(c);
					g.chain_sz.push_back(0);
					dfs_hld(g, c, v, g.chain_sz.size()-1);
				} else {
					dfs_hld(g, c, v, nchain);
				}
			}
			
		}
	}
}

static BF fcompose(const BF &l, const BF &r) {
	return BF {l.l(l.r), r.r(r.l)};
}

/* Build Heavy-Light decomposition and SegTree for each chain */
void bld_hld(G &g) {
	int tick = 0;
	dfs_sizes(g, 0, -1, tick);
	g.chain_root.push_back(0);
	g.chain_sz.push_back(0);
	dfs_hld(g, 0, -1, 0);
	for (auto sz:g.chain_sz)
		g.chain.push_back(SegTree<BF>(sz, fcompose));
}

void do_set(G &g, int node, const F &f) {
	BF bf = {f, f}; 
	g.chain[g.nchain[node]].set(g.nchpos[node], bf);
}

int do_query(const G &g, int a, int b, int x) {
	F a_res = {1, 0};
	while (not_parent(g, g.chain_root[g.nchain[a]], b)) {
		a_res = g.chain[g.nchain[a]](0, g.nchpos[a]+1).l(a_res);
		a = g.parent[g.chain_root[g.nchain[a]]];
	}
	F b_res = {1, 0};
	while (not_parent(g, g.chain_root[g.nchain[b]], a)) {
		b_res = b_res(g.chain[g.nchain[b]](0, g.nchpos[b]+1).r);
		b = g.parent[g.chain_root[g.nchain[b]]];
	}
	if (g.nchpos[a] < g.nchpos[b]) {
		auto f = b_res(g.chain[g.nchain[a]](g.nchpos[a], g.nchpos[b]+1).r(a_res));
		return f(x);
	} else {
		auto f = b_res(g.chain[g.nchain[a]](g.nchpos[b], g.nchpos[a]+1).l(a_res));
		return f(x);
	}
}

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	G g(n);
	for (int i=0; i<n-1; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		g.ee[f].push_back(t);
		g.ee[t].push_back(f);
	}
	bld_hld(g);
#if 0
	while (q--) {
		int q, u, x;
		scanf("%d%d%d", &q, &u, &x);
		switch(q) {
		case 1:
			do_set(g, u, x);
			break;
		default:
			printf("%d\n", do_query(g, u, x));
		}
	}
#endif
	return 0;
}
