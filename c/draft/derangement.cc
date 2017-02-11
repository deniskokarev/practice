#include <iostream>
#include <vector>
#include <cassert>
/*
 * calculate number of derangements of N
 * cached version
 */

using namespace std;

uint64_t choose_c(uint8_t n, uint8_t k) {
	assert(k >= 0 && k <= n);
	static vector<vector<uint64_t> > cache;
	if (k > n/2)
		k = n-k;
	for (auto i=cache.size(); i<n+1; i++) {
		vector<uint64_t> kv((i+1)/2+1);
		cache.push_back(kv);
	}
	if (!cache[n][k]) {
		if (k == 0) {
			cache[n][k] = 1;
		} else if (k == 1) {
			cache[n][k] = n;
		} else {
			cache[n][k] = choose_c(n-1, k-1) + choose_c(n-1, k);
		}
	}
	return cache[n][k];
}

class fact_c {
	static const int max = 22;
	uint64_t cache[max];
public:
	fact_c() {
		cache[0] = 1;
		for (int i=1; i<max; i++)
			cache[i] = cache[i-1]*i;
	}
	uint64_t operator()(uint8_t n) const {
		assert(n >= 0 && n < max);
		return cache[n];
	}
};

static fact_c fact;

uint64_t derangement_c(uint8_t n) {
	assert(n >= 0 && n < 21);
	static vector<uint64_t> cache(21);
	uint64_t sum;
	uint8_t i, j;
	if (!cache[n]) {
		if (n<2) {
			cache[0] = 0;
			cache[1] = 0;
		} else if (n == 2) {
			cache[2] = 1;
		} else {
			sum = fact(n);
			for (i=n-1, j=1; i>1; i--,j++)
				sum -= choose_c(n, j)*derangement_c(i);
			sum -= 1;
			cache[n] = sum;
		}
	}
	return cache[n];
}

int main(int argc, char **argv) {
	if (argc > 1) {
		int n = atoi(argv[1]);
		if (n > 1 && n < 21) { 
			cout << derangement_c(n) << endl;
			return 0;
		} else {
			cerr << "n must be in [2..20]" << endl;
			return -2;
		}
	} else {
		cerr << "Calculating number of derangements over N:\nUsage:\n\t" << argv[0] << " <n>\n";
		cerr << "where n must be greater than one\n";
		return -1;
	}
}
