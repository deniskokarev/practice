/* ACMP 112 problem */

/**
 * organize Fenwick tree over a random iterator
 * inc(pos, delta) in O(log(n))
 * sum(0..last) in O(log(n))
 */
#include <iterator>
#include <algorithm>

template<typename IT> struct FenwickTree {
	using value_type = typename std::iterator_traits<IT>::value_type;
	using difference_type = typename std::iterator_traits<IT>::difference_type;
    IT vv;
	int sz;
	// initialize the tree with 0s 
    FenwickTree(IT begin, IT end):vv(begin),sz(end-begin) {
		std::fill(begin, end, 0);
	}
	// increment the element at pos by delta
    void inc(difference_type pos, value_type delta) {
        do vv[pos] += delta; while((pos=pos|(pos+1)) < sz);
    }
    // @return sum[0..last]
    value_type sum(difference_type last) {
        value_type sum = 0;
        do sum += vv[last]; while ((last=(last&(last+1))-1) >= 0);
        return sum;
    }
};

// helper function to simplify the use
template<typename IT> FenwickTree<IT> create_fenwick(IT b, IT e) {
	return FenwickTree<IT>(b, e);
}

#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
	int n, k;
	scanf("%d %d", &n, &k);
	assert(n<=10000);
	unsigned short solders[n+1];
	unsigned long long ans = 0;
	for (int ki=0; ki<k; ki++) {
		auto fw = create_fenwick(solders, solders+n+1);
		for (int i=0; i<n; i++) {
			unsigned short s;
			scanf("%hu", &s);
			ans += i-fw.sum(s);
			fw.inc(s, 1);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
