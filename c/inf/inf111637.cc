/* ROI 2013E */

/*
 * Compute upper bound of logarithm for an integer argument
 * Example:
 *    int l = ilog<2>(n);
 * which computes
 *	  int l = (n==0) ? 0 : int(ceil(log2(n)))
 * The log<N>() code is taking advantage of C++11 template engine, which unrolls
 * the statement into the binary decision ?: operator at compile time.
 * This way ilog<2>(i) is about x10 faster than int(ceil(log2(i)))
 * and x3 faster than doing similar binary search in a loop.
 * The template implementation is enven sligthly faster that its "C" counterpart
 * log2_u32(i) function (see genilog.sh)
 * The logarithm base is a constexpr integer
 */

#include <type_traits>

namespace __ilog {

	template<typename N, N b, int p> struct ipow {
		static constexpr N value = N(ipow<N,b,p-1>::value*b);
	};

	template<typename N, N b> struct ipow<N,b,0> {
		static constexpr N value = 1;
	};

	template<typename UI, int base, int f, int t> struct _ilog {
		static int eval(UI n) {
			constexpr int m = (f+t)/2;
			return (n <= ipow<UI,base,m>::value) ? _ilog<UI,base,f,m>::eval(n) : _ilog<UI,base,m+1,t>::eval(n);
		}
	};

	template<typename UI, int base, int f> struct _ilog<UI,base,f,f> {
		static int eval(UI n) {
			return f;
		}
	};

	template<int p> struct val {
		static constexpr int value = p;
	};
		
	template<typename UI, int b, int p, unsigned long long mx> struct _ipowmax {
		static constexpr int value = std::conditional<(UI(mx) < UI(mx*b)), _ipowmax<UI, b, p+1, mx*b>, val<p>>::type::value; 
	};

	template<typename UI, int b> struct ipowmax {
		static constexpr int value = _ipowmax<UI, b, 0, 1>::value;
	};
	
	template<typename UI, int b> struct ilog {
		static int eval(UI n) {
			return _ilog<UI,b,0,ipowmax<UI,b>::value+1>::eval(n);
		}
	};

};

template<int base> int ilog(unsigned char n) { return __ilog::ilog<unsigned char, base>::eval(n); }
template<int base> int ilog(unsigned short n) { return __ilog::ilog<unsigned short, base>::eval(n); }
template<int base> int ilog(unsigned int n) { return __ilog::ilog<unsigned int, base>::eval(n); }
template<int base> int ilog(unsigned long n) { return __ilog::ilog<unsigned long, base>::eval(n); }
template<int base> int ilog(unsigned long long n) { return __ilog::ilog<unsigned long long, base>::eval(n); }

/*
 * Static Range Minimum Query structure
 * may be filled only in sequential right to left order
 * while already allowing queries on the processed tail
 */
#include <vector>
#include <stdexcept>

template<class T> class RMQ {
	using difference_type = unsigned;
	class Val {
		friend class RMQ;
		friend class Iterator;
		RMQ &parent;
		difference_type pos;
		Val(RMQ &parent, difference_type pos):parent(parent),pos(pos) {}
	public:
		void operator=(const T &val) {
			parent.set(pos, val);
		}
	};
	class Iterator {
		friend class RMQ;
		friend class RMQ_Val;
		RMQ &parent;
		difference_type pos;
		Iterator(RMQ &parent, difference_type pos):parent(parent),pos(pos) {}
	public:
		void operator++() {
			pos--;
		}
		Val operator*() {
			return Val(parent, pos);
		}
		bool operator==(const Iterator &it) const {
			return pos == it.pos;
		}
	};
	difference_type sz;
	difference_type lvls;
	std::vector<std::vector<T>> rmq;
	void set(difference_type pos, const T &val) {
		rmq[0][pos] = val;
		for (int l=1,p2=1; l<lvls; l++,p2*=2)
			rmq[l][pos] = std::min(rmq[l-1][pos], rmq[l-1][std::min(pos+p2, sz-1)]);
	}
public:
	RMQ(difference_type sz): sz(sz), lvls(ilog<2>(sz+1)), rmq(lvls, std::vector<T>(sz)) {
	}
	T operator()(difference_type begin, difference_type end) const {
		difference_type len = end-begin;
		if (len < 1) {
			throw std::invalid_argument("end must be greater than begin");
		} else if (len == 1) {
			return rmq[0][begin];
		} else {
			difference_type l = ilog<2>(len)-1;
			difference_type p2 = 1<<(l);
			return std::min(rmq[l][begin], rmq[l][end-p2]);
		}
	}
	Iterator rbegin() {
		return Iterator(*this, sz-1);
	}
	Iterator rend() {
		return Iterator(*this, -1);
	}
};

/* MAIN ROI 2013E */

#include <cstdio>
#include <cstring>
#include <climits>

constexpr int FT_MAX = 300001; // max fuel type
constexpr int INF = INT_MAX/2;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int ff[n];              // fuel types
	for (auto &f:ff)
		scanf("%d", &f);
	int nxt[n];             // planet direct hops
	nxt[n-1] = n-1;
	int f2p[FT_MAX];        // fuel type -> planet pos
	memset(f2p, 0, sizeof(f2p));
	f2p[ff[n-1]] = n-1;
	for (int i=n-2; i>=0; i--) {
		auto &prev = f2p[ff[i]];
		if (prev != 0)
			nxt[i] = prev;
		else
			nxt[i] = -1;
		prev = i;
	}
	struct P {
		int hops;
		int nxt;
	} ppdp[n];
	RMQ<std::pair<int,int>> rmq(n);		// fill RMQ of [hops,pos] pairs from right to left
	auto rmq_it = rmq.rbegin();
	*rmq_it = std::make_pair(0, n-1);
	++rmq_it;
	for (int i=n-2; i>=0; i--,++rmq_it) {
		if (nxt[i] > 0) {
			auto best_hop = rmq(i+1, nxt[i]+1);
			ppdp[i] = P {best_hop.first+1, int(best_hop.second)};
			*rmq_it = std::make_pair(ppdp[i].hops, i);
		} else {
			ppdp[i] = P {INF, INF};
			*rmq_it = std::make_pair(INF, INF);
		}
	}
	if (ppdp[0].hops < INF) {
		printf("%d\n", ppdp[0].hops);
		for (int pi=0; pi!=n-1; pi=ppdp[pi].nxt)
			printf("%d ", pi+1);
		printf("\n");
	} else {
		printf("0\n");
	}
	return 0;
}
