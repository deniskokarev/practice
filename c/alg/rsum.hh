/*
 * Sum on the range supporting O(log(n)) updates and O(log(n)) sum
 * The storage is O(2*n)
 */
#include <vector>

template<typename N> class RangeSum {
	using Container = std::vector<N>;
	using SZ = typename Container::difference_type;
	SZ sz;
	SZ psz;
	Container vv;
public:
	RangeSum(SZ _sz):sz(_sz) {
		psz = (1ULL<<int(ceil(log2(sz))))-1; // or use ilog<2>(sz) from ilog.hh
		vv.resize(psz+sz);
	}
	void add(SZ pos, N v) {
		SZ p = pos+psz+1;
		while (p>0) {
			vv[p-1] += v;
			p >>= 1;
		}
	}
	const N total() const {
		return vv[0];
	}
	const N gt(SZ pos) const {
		N rc = 0;
		if (pos<sz-1) {
			SZ p = pos+psz+1;
			while (p>0) {
				if ((p & 1) == 0)
					rc += vv[p]; // add right sibling
				p >>= 1;
			}
		}
		return rc;
	}
	const N ge(SZ pos) const {
		if (pos < sz)
			return gt(pos)+vv[pos+psz];
		else
			return 0;
	}
	const N between(SZ b, SZ e) const {
		return ge(b)-ge(e);
	}
};
