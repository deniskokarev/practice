#include <cstdio>
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

constexpr int SZ = 5e5+1;

struct MyInt {
	int n;
	MyInt(int _n):n(_n){}
	MyInt():MyInt(INT_MAX){} // for min
	operator int() const {
		return n;
	}
};

struct MinInt {
	int operator()(const MyInt &a, const MyInt &b) const {
		return std::min(a, b);
	}
};

int main(int argc, char **argv) {
	int m, k, n, s;
	scanf("%d%d%d%d", &m, &k, &n, &s);
	const int nk = n*k;
	vector<int> aa(m);
	for (auto &a:aa)
		scanf("%d", &a);
	int btypes = 0; // number of various kinds of bs
	vector<int> bmap(SZ, -1); // a->btype
	vector<int> bb(SZ, 0);	// btype->cnt
	for (int i=0; i<s; i++) {
		int b;
		scanf("%d", &b);;
		if (bmap[b] == -1)
			bmap[b] = btypes++;
		bb[bmap[b]]++;
	}
	vector<deque<int>> ps(btypes);
	for (int i=0; i<btypes; i++)
		for (int j=0; j<bb[i]; j++)
			ps[i].push_back(-1);
	BotUpSegTree<MyInt, MinInt> mn(btypes);
	for (int i=0; i<btypes; i++)
		mn.set(i, ps[i].front());
	int fstp = -1;
	for (int i=0; i<m; i++) {
		int a = aa[i];
		if (bmap[a] != -1) {
			int b = bmap[a];
			ps[b].push_back(i);
			ps[b].pop_front();
			int pb = ps[b].front();
			mn.set(b, pb);
			//cerr << "b=[" << b << "] = " << pb << endl;
			fstp = mn();
		}
		int rmk = i-fstp+1-k; // must remove this many between i and fstp to fit into k
		int npluck;
		if (rmk >= 0)
			npluck = rmk + fstp%k;
		else
			npluck = (i+1)%k;
		//cerr << "i=" << i << " fstp=" << fstp << " rmk=" << rmk << " npluck=" << npluck << endl;
		if (fstp >= 0 && m-npluck >= nk) {
			printf("%d\n", npluck);
			if (rmk >= 0) {
				for (int j=i; j>=0 && rmk; j--) {
					int b = bmap[aa[j]];
					if (b < 0 || bb[b] <= 0) {
						printf("%d ", j+1);
						rmk--;
					}
					if (b >= 0)
						bb[b]--;
				}
				int more = fstp%k;
				for (int j=0; j<more; j++)
					printf("%d ", j+1);
			} else {
				int more = (i+1)%k;
				for (int j=0; j<more; j++)
					printf("%d ", j+1);
			}
			printf("\n");
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
