#ifndef __BINOMIAL_HH
#define __BINOMIAL_HH

#include <cinttypes>

/**
 * Constant binomial coefficients computation
 */
namespace binomial {
	template <int N, int K> struct Binomial {
		static constexpr uint64_t value = Binomial<N-1, K-1>::value + Binomial<N-1, K>::value;
	};
	template <int N> struct Binomial<N, N> {
		static constexpr uint64_t value = 1;
	};
	template <int N> struct Binomial<N, 0> {
		static constexpr uint64_t value = 1;
	};
	template <int N, int K> constexpr uint64_t choose() {
		return binomial::Binomial<N, K>::value;
	}
}

/** constexpr macro to be used at compile time */
#define CHOOSE(N, K) binomial::choose<N, K>()

#endif // __BINOMIAL_HH
