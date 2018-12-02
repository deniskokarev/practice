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

constexpr int DF = -100;
constexpr int DT = +100;
constexpr int SZ = CHOOSE(DT-DF+3-1, 3);
Brick ans[SZ];

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	int64_t l = isqrt(n/6);
	// trying bricks with [a-D..a+D] side variations
	int ai = 0;
	for (int i=DF; i<DT; i++)
		for (int j=i; j<DT; j++)
			for (int k=j; k<DT; k++)
				ans[ai++] = Brick {max(l+i, int64_t(0)), max(l+j, int64_t(0)), max(l+k, int64_t(0))};
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
