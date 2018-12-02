#ifndef __BINOMIAL_HH
#define __BINOMIAL_HH

#include <cinttypes>

/**
 * Constant binomial coefficients computation
 */
namespace binomial {
	template <unsigned N, unsigned K, unsigned C> struct Binomial {
		static constexpr uint64_t value = Binomial<N, K, C-1>::value * (N-K+C) / C;
	};
	template <unsigned N, unsigned K> struct Binomial<N, K, 1> {
		static constexpr uint64_t value = N - K + 1;
	};
	template <unsigned N, unsigned K> constexpr uint64_t choose() {
		return binomial::Binomial<N, K, K>::value;
	}
}

/** constexpr macro to be used at compile time */
#define CHOOSE(N, K) binomial::choose<N, K>()

#endif // __BINOMIAL_HH
