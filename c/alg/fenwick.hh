/**
 * Fenwick tree implementation
 * inc(pos, delta) in O(log(n))
 * sum(0..last) in O(log(n))
 */

#include <vector>

template<typename N> struct FenwickTree {
    using Container = std::vector<N>;
    using SZ = typename Container::difference_type;
    SZ sz;
    Container vv;
    FenwickTree(SZ _sz):sz(_sz),vv(sz,0){}
    void inc(SZ pos, N delta) {
        do vv[pos] += delta; while((pos=pos|(pos+1)) < sz);
    }
    // @return sum[0..last]
    N sum(SZ last) {
        N sum = 0;
        do sum += vv[last]; while ((last=(last&(last+1))-1) >= 0);
        return sum;
    }
};
