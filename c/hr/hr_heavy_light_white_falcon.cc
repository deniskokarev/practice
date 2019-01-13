#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
/* Hackerrank https://www.hackerrank.com/challenges/heavy-light-white-falcon */
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
	FOLD_OP fold; // "fold" operator to be executed on our interval
	/**
	 * If you touched values directly, you must perform rebuild()
	 */
	void rebuild() {
		for (int i=sz+sz-1; i>1; i-=2)
			tree[i>>1] = fold(tree[i-1], tree[i]);
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

struct G {
	int sz;
	vector<vector<int>> ee;
	vector<int> parent;
	vector<int> size;
	vector<int> t_in, t_out;
	vector<int> nchain;
	vector<int> nchpos;
	vector<int> chain_root;
	vector<int> chain_sz;
	vector<SegTree<int>> chain;
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

bool is_parent(const G &g, int p, int c) {
	return g.t_in[p] <= g.t_in[c] && g.t_out[c] <= g.t_out[p];
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

static int max_fold(int a, int b) {
	return max(a, b);
}

/* Build Heavy-Light decomposition and SegTree for each chain */
void bld_hld(G &g) {
	int tick = 0;
	dfs_sizes(g, 0, -1, tick);
	g.chain_root.push_back(0);
	g.chain_sz.push_back(0);
	dfs_hld(g, 0, -1, 0);
	for (auto sz:g.chain_sz)
		g.chain.push_back(SegTree<int>(sz, max_fold));
}

void do_set(G &g, int node, int val) {
	g.chain[g.nchain[node]].set(g.nchpos[node], val);
}

int do_query(const G &g, int a, int b) {
	int res = 0;
	while (!is_parent(g, g.chain_root[g.nchain[a]], b)) {
		res = max_fold(res, g.chain[g.nchain[a]](0, g.nchpos[a]+1));
		a = g.parent[g.chain_root[g.nchain[a]]];
	}
	while (!is_parent(g, g.chain_root[g.nchain[b]], a)) {
		res = max_fold(res, g.chain[g.nchain[b]](0, g.nchpos[b]+1));
		b = g.parent[g.chain_root[g.nchain[b]]];
	}
	if (g.nchpos[a] > g.nchpos[b])
		swap(a, b);
	return max_fold(res, g.chain[g.nchain[a]](g.nchpos[a], g.nchpos[b]+1));
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
	return 0;
}
