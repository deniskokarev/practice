#include <iostream>
#include <algorithm>
#include <limits.h>
/* ROI 2010 A problem */
using namespace std;

int64_t isqrt(int64_t s) {
	int64_t f=1, t=INT_MAX;
	while (f<t) {
		int64_t m = f+(t-f)/2;
		if (m*m <= s)
			f = m+1;
		else
			t = m;
	}
	return f-1;
}

struct Brick {
	int64_t a, b, c;
	int64_t area() const {
		return a*b*2 + b*c*2 + c*a*2;
	}
	int64_t volume() const {
		return a*b*c;
	}
};

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

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	int64_t a = isqrt(n/6);
	// trying bricks with [a-D..a+D] side variations
	constexpr int DF = -3;
	constexpr int DT = +3;
	constexpr int SZ = CHOOSE(DT-DF+3-1, 3);
	Brick ans[SZ];
	int ai = 0;
	for (int i=DF; i<DT; i++)
		for (int j=i; j<DT; j++)
			for (int k=j; k<DT; k++)
				ans[ai++] = Brick {max(a+i, 0LL), max(a+j, 0LL), max(a+k, 0LL)};
	sort(ans, ans+SZ, [](const Brick &a, const Brick &b){return a.volume() > b.volume();});
	for (auto &a:ans) {
		if (a.area() <= n) {
			cout << a.volume() << endl;
			cout << a.a << ' ' << a.b << ' ' << a.c << endl;
			break;
		}
	}
	return 0;
}
