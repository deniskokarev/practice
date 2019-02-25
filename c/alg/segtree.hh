#ifndef __SEGTREE_HH__
#define __SEGTREE_HH__

#include <functional>
#include <vector>
#include <cmath>

/**
 * Simple Segment tree on a vector with custom "fold" operation.
 * Supports setting a value at a position and "folding" values on a range
 * Typically, folding would be operator+() or max()
 * O(2*n) space
 * set() - O(NlogN) time
 * fold() - O(NlogN) time
 * @author Denis Kokarev
 */
template<class ValueType=int> class SegTree {
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
	 * @param _fold  - custom fold operator - default std::plus
	 */
	SegTree(int _sz, FOLD_OP _fold=std::plus<value_type>()):sz(_sz),tree(sz+sz),fold(_fold) {
	}

	/**
	 * Alternative constructor to initialize the values right away
	 * Works in O(n)
	 * @param list - list of given values
	 * @param _fold  - custom fold operator - default std::plus
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

/**
 * Segment tree to perform "lazy" increments on all values in the open interval [b, e)
 */
template<class ValueType=int> class AddSegTree {
	using value_type = ValueType;
	using INC_OP = std::function<void(value_type &, const value_type &)>;
	int sz;
	int l2;
	std::vector<value_type> tree; // where we keep all values (first sz elements are aggreagates)
	INC_OP inc; // "increment" operator to be executed during increments
	/**
	 * Propagate increments down to a specific element in O(logN)
	 */
	void propagate_inc(int pos) {
		for (int l=l2; l>0; l--) {
			int p = pos >> l;
			inc(tree[p<<1], tree[p]);
			inc(tree[(p<<1)|1], tree[p]);
			tree[p] = value_type();
		}
	}
	/**
	 * Propagate all increments to values in O(n)
	 */
	void propagate_inc() {
		for (int i=1; i < sz; i++) {
			inc(tree[i<<1], tree[i]);
			inc(tree[(i<<1)|1], tree[i]);
			tree[i] = value_type();
		}
	}
	static void default_inc(value_type &a, const value_type &b) {
		a += b;
	};
public:
	/**
	 * Create segment tree with given size and custom inc operator
	 * Upon creation all values will be zeros
	 * @param _sz - maximum size
	 * @param _add  - custom add operator - default std::plus
	 */
	AddSegTree(int _sz, INC_OP _inc=default_inc):sz(_sz),l2(floor(log2(sz))),tree(sz+sz),inc(_inc) {
	}

	AddSegTree(const std::initializer_list<value_type> &list, INC_OP _inc=default_inc):AddSegTree(list.size(), _inc) {
		std::copy(list.begin(), list.end(), tree.begin()+sz);
	}
	
	/**
	 * Perform "lazy" increment by v on all values in the open interval [b, e)
	 * Runs in O(logN)
	 */ 
	void add_each(int b, int e, const value_type &v) {
		b += sz;
		e += sz;
		while (b < e) {
			if (b&1)
				inc(tree[b++], v);
			if (e&1)
				inc(tree[--e], v);
			b >>= 1;
			e >>= 1;
		}
	}

	/**
	 * Perform "lazy" increment by v to all values
	 * Runs in O(logN)
	 */ 
	void add_each(const value_type &v) {
		add_each(0, sz, v);
	}
	
	/**
	 * Get the value at position pos in O(logN)
	 */
	const value_type &get(int pos) {
		int node = sz+pos;
		propagate_inc(node);
		return tree[node];
	}
	
	/**
	 * Or if want to iterate all recomputed values
	 * Needs O(n) to precompute
	 */
	typename std::vector<value_type>::const_iterator begin() {
		propagate_inc();
		return tree.cbegin() + sz;
	}
	
	typename std::vector<value_type>::const_iterator end() {
		return tree.cend();
	}
};

#endif //__SEGTREE_HH__
