/* ACMP 304 */

/* composition of http://e-maxx.ru/algo/big_integer */
#include <vector>
#include <cstdio>
#include <cassert>
#include <string>

struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	lnum10(uint64_t n):a() {
		if (n>0) {
			while (n>0) {
				a.push_back(n%base);
				n /= base;
			}
		} else {
			a.push_back(0);
		}
	}
	std::string to_string() const {
		char buf[11];
		buf[10] = 0;
		snprintf(buf, 10, "%d", a.empty() ? 0 : a.back());
		std::string s(buf);
		for (int i=(int)a.size()-2; i>=0; --i) {
			snprintf(buf, 10, "%09d", a[i]);
			s.append(buf);
		}
		return s;
	}
	void operator*=(const lnum10 &b) {
		VEC c(a.size()+b.a.size());
		for (size_t i=0; i<a.size(); ++i) {
			for (int j=0, carry=0; j<(int)b.a.size() || carry; ++j) {
				long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.a.size() ? b.a[j] : 0) + carry;
				c[i+j] = int (cur % base);
				carry = int (cur / base);
			}
		}
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();
		a = c;
	}
};

using namespace std;

/**
 * Binomial coefficient (choose n, k)
 */
uint64_t choose(int n, int k) {
	assert(k <= n);
	uint64_t res = 1;
	for (int i=n,j=1; j<=k; i--,j++) {
		res *= i;
		res /= j;
		assert(res > 0);	// 64bit overflow
	}
	return res;
}

uint64_t variants(int n, int m, int sc) {
	uint64_t ans;
	/* paths on the rectangular grid upto 24x24 (winning sc) */
	if (n>sc) {
		/* after reaching 24x24 we can walk with only 2 variants per score point */
		ans = choose(sc+sc, sc);
		ans *= (1ULL << (n-sc));
	} else {
		if (m>sc) {
			ans = choose(n+sc, n);
		} else {
			// technically nobody wins
			ans = choose(n+m, n);
		}
	}
	return ans;
}

int main(int argc, char **argv) {
	int cnt;
	int a, b;
	assert(scanf("%d", &cnt) == 1);
	lnum10 ans(1);
	for (int i=0; i<cnt && i<4; i++) {
		assert(scanf("%d:%d", &a, &b) == 2);
		int n = min(a, b);
		int m = max(a, b);
		ans *= lnum10(variants(n, m, 24));
	}
	if (cnt > 4) {
		assert(scanf("%d:%d", &a, &b) == 2);
		int n = min(a, b);
		int m = max(a, b);
		ans *= lnum10(variants(n, m, 14));
	}
	printf("%s\n", ans.to_string().c_str());
	return 0;
}
