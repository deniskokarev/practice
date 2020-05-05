/**
 * Segment tree to perform range increments on all values in the open interval [b, e)
 * Then you can gen any element in O(logN)
 * or recompute all elements in O(N)
 */
template<class ValueType=int> class TopDownSegTree {
	using value_type = ValueType;
	int sz;
	int l2;
	std::vector<value_type> tree; // where we keep all values (first sz elements are aggreagates)
	/**
	 * Propagate increments down to a specific element in O(logN)
	 */
	void propagate_inc(int pos) {
		for (int l=l2; l>0; l--) {
			int p = pos >> l;
			tree[p<<1] += tree[p];
			tree[(p<<1)|1] += tree[p];
			tree[p] = value_type();
		}
	}
	/**
	 * Propagate all increments to values in O(n)
	 */
	void propagate_inc() {
		for (int i=1; i < sz; i++) {
			tree[i<<1] += tree[i];
			tree[(i<<1)|1] += tree[i];
			tree[i] = value_type();
		}
	}
public:
	/**
	 * Create segment tree with given size
	 * Upon creation all values will be zeros
	 * @param sz - maximum size
	 */
	TopDownSegTree(int sz):sz(sz),l2(floor(log2(sz))),tree(sz+sz) {
	}

	TopDownSegTree(const std::initializer_list<value_type> &list):TopDownSegTree(list.size()) {
		std::copy(list.begin(), list.end(), tree.begin()+sz);
	}
	
	/**
	 * Perform "lazy" increment by v on all values in the open interval [b, e)
	 * Runs in O(logN)
	 */ 
	void inc(int b, int e, const value_type &v) {
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

	/**
	 * Get the value at position pos in O(logN)
	 */
	const value_type &get(int pos) {
		pos += sz;
		propagate_inc(pos);
		return tree[pos];
	}
	
	/**
	 * Or if want to recompute all values and iteratite them
	 * Needs O(N) to precompute
	 */
	typename std::vector<value_type>::const_iterator begin() {
		propagate_inc();
		return tree.cbegin() + sz;
	}
	
	typename std::vector<value_type>::const_iterator end() {
		return tree.cend();
	}
};

struct MyBool {
	int val;
	MyBool():val(0) {
	}
	MyBool(int v):val(v) {
	}
	operator int() const {
		return val;
	}
	void operator+=(const MyBool &o) {
		val ^= o.val;
	}
};

class Solution {
public:
	static int minKBitFlips(const vector<int>& aa, int k) {
		int sz = aa.size();
		TopDownSegTree<MyBool> tree(sz);
		for (int i=0; i<sz; i++)
			tree.inc(i, i+1, MyBool(aa[i]));
		int ans = 0;
		for (int i=0; i<=sz-k; i++) {
			if (tree.get(i) == 0) {
				ans++;
				tree.inc(i, i+k, MyBool(1));
			}
		}
		for (int i=sz-k+1; i<sz; i++)
			if (tree.get(i) == 0)
				ans = -1;
		return ans;
	}
};

