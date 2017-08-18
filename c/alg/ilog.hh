#ifndef __ILOG_HH__
#define __ILOG_HH__

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

template<int base> int ilog(signed char n) { return __ilog::ilog<unsigned char, base>::eval(n); }
template<int base> int ilog(signed short n) { return __ilog::ilog<unsigned short, base>::eval(n); }
template<int base> int ilog(signed int n) { return __ilog::ilog<unsigned int, base>::eval(n); }
template<int base> int ilog(signed long n) { return __ilog::ilog<unsigned long, base>::eval(n); }
template<int base> int ilog(signed long long n) { return __ilog::ilog<unsigned long long, base>::eval(n); }

#endif // __ILOG_HH__
