#ifndef __SEGTREE_HH__
#define __SEGTREE_HH__
/**
 * Segment tree on a vector with custom "fold" operation
 * Supports setting a value at position and "folding" values
 * in a given range. Both in O(logN) time
 * Takes O(n) space (about 2*n)
 * @author Denis Kokarev
 */
#include <functional>
#include <vector>
#include <cmath>

template<class T=int> class SegmentTree {
	using value_type = T;
	using OP = std::function<value_type(value_type,value_type)>;
	int sz;
	int pad;
	std::vector<value_type> vv; // where we keep all values, first pad elements are aggreagates
	/**
	 * size of padding necessary to keep array of size pad+sz in a perfect binary tree
	 */
	static int getPadSize(int sz) {
		return (1<<int(ceil(log2(sz))))-1;
	}
	OP fold; // "fold" operator to be executed on our interval
public:
	/**
	 * Create segment tree with given size and custom fold operator
	 * Upon creation all values will be zeros
	 * @param _sz - maximum size
	 * @param _fold  - custom fold operator - default std::plus
	 */
	SegmentTree(int _sz, OP _fold=std::plus<value_type>()):sz(_sz),pad(getPadSize(sz)),vv(pad+sz),fold(_fold) {
	}

	/**
	 * Perform online update in O(logN)
	 * @param pos
	 * @param v
	 */
	void set(int pos, const value_type v) {
		int node = pad+pos;
		vv[node] = v;
		int parent = (node-1)/2;
		if (parent*2+2 < pad+sz)
			vv[parent] = fold(vv[parent*2+1], vv[parent*2+2]);
		else
			vv[parent] = vv[node];
		node = parent;
		for (parent=(node-1)/2; node>0; node=parent,parent=(node-1)/2)
			vv[parent] = fold(vv[parent*2+1], vv[parent*2+2]);
	}

	/**
	 * Perform interval folding on open-ended [b, e) segment. Runs in O(logN)
	 * @param b - begin - first element inclusive
	 * @param e - end - element after last
	 * @return fold(vv[b], fold(vv[b+1], fold(vv[b+2], ... fold(vv[e-2], fold(vv[e-1])...)))
	 */
	value_type operator()(int b, int e) const {
		b += pad;
		e += pad;
		if (e-b > 1) {
			value_type vb = vv[b++];
			value_type ve = vv[--e];
			while (b < e) {
				int pb = (b+1)/2; // parent b
				int pe = (e-1)/2; // parent e
				if (!(b&1))
					vb = fold(vb, vv[b]);
				else if (pb <= pe)
					vb = fold(vb, vv[pb-1]);
				if (!(e&1))
					ve = fold(vv[e-1], ve);
				b = pb;
				e = pe;
			}
			return fold(vb, ve);
		} else {
			return vv[b];
		}
	}
};

#endif //__SEGTREE_HH__
