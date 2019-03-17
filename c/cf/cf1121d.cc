#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
/* CodeForces CF1121D problem */

#include <cmath>

/**
 * Simple bottom-up Segment tree on a vector with custom "fold" operation.
 * Supports setting a value at a position and "folding" values on a range
 * Typically, folding would be std::plus
 * O(2*n) space
 * set() - O(NlogN) time
 * fold() - O(NlogN) time
 * @author Denis Kokarev
 */
template<class ValueType=int, class FoldOp=std::plus<ValueType>> class BotUpSegTree {
	using value_type = ValueType;
	int sz;
	std::vector<value_type> tree; // where we keep all values, first sz elements are aggreagates
	/**
	 * If you touched values directly, you must perform rebuild()
	 */
	void rebuild() {
		for (int i=sz+sz-1; i>1; i-=2)
			tree[i>>1] = FoldOp()(tree[i-1], tree[i]);
	}
public:
	/**
	 * Create segment tree with given size and custom fold operator
	 * Upon creation all values will be zeros
	 * @param _sz - maximum size
	 * @param _fold  - custom fold operator - default std::plus
	 */
	BotUpSegTree(int sz):sz(sz),tree(sz+sz) {
	}

	/**
	 * Alternative constructor to initialize the values right away
	 * Works in O(n)
	 * @param list - list of given values
	 * @param _fold  - custom fold operator - default std::plus
	 */
	BotUpSegTree(const std::initializer_list<value_type> &list):BotUpSegTree(list.size()) {
		std::copy(list.begin(), list.end(), tree.begin()+sz);
		rebuild();
	}
	
	/**
	 * Perform online update in O(logN)
	 * @param pos
	 * @param v
	 */
	void set(int pos, const value_type &v) {
		pos += sz;
		tree[pos] = v;
		for (pos=pos>>1; pos>0; pos >>= 1)
			tree[pos] = FoldOp()(tree[pos<<1], tree[(pos<<1)|1]);
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
			value_type vb = value_type();
			value_type ve = value_type();
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
	/**
	 * Perform entire interval folding
	 * @return fold(tree[b], fold(tree[b+1], fold(tree[b+2], ... fold(tree[e-2], fold(tree[e-1])...)))
	 */
	value_type operator()() {
		return operator()(0, sz);
	}
};

using namespace std;

constexpr int SZ = 1e5+1;

struct MaxInt {
	int operator()(int a, int b) const {
		return std::max(a, b);
	}
};

int main(int argc, char **argv) {
	int m, k, n, s;
	cin >> m >> k >> n >> s;
	vector<int> aa(m);
	for (auto &a:aa)
		cin >> a;
	int btypes = 0; // number of various kinds of bs
	vector<int> bmap(SZ, -1); // a->btype
	vector<int> bb(SZ, 0);	// btype->cnt
	for (int i=0; i<s; i++) {
		int b;
		cin >> b;
		if (bmap[b] == -1)
			bmap[b] = btypes++;
		bb[bmap[b]]++;
	}
	vector<deque<int>> ps(btypes);
	for (int i=0; i<btypes; i++)
		for (int j=0; j<bb[i]; j++)
			ps[i].push_back(INT_MAX);
	BotUpSegTree<int, MaxInt> mx(btypes);
	for (int i=0; i<btypes; i++)
		mx.set(i, ps[i].front());
	vector<int> pluck;
	for (int i=m-1; i>=0; i--) {
		int a = aa[i];
		if (bmap[a] != -1) {
			int b = bmap[a];
			ps[b].push_back(i);
			if (ps[b].front() < INT_MAX)
				pluck.push_back(aa[ps[b].front()]);
			ps[b].pop_front();
			int pb = ps[b].front();
			mx.set(b, pb);
			int mn = mx();
			//cerr << "b=" << b << " pb=" << pb << " mn=" << mn << " i=" << i << " diff=" << mn-i << endl;
			if (mn < INT_MAX) {
				int npluck = mn-i-s+1;
				if ((m-npluck) >= n*k) {
					cout << npluck << endl;
					for (int j=npluck-1; j>=0; j--)
						cout << pluck[j]+1 << " ";
					cout << endl;
					return 0;
				}
			}
		} else {
			pluck.push_back(i);
		}
	}
	cout << -1 << endl;
	return 0;
}
