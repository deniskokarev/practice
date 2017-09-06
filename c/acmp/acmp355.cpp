/* ACMP 355 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	assert(n < 21);	// 64bit overflow with n>=21
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	size_t sz = fact(s.length());
	vector<string> pp(sz);
	for (auto &p:pp) {
		p = s;
		next_permutation(s.begin(), s.end());
	}
	sort(pp.begin(), pp.end());
	auto e = unique(pp.begin(), pp.end());
	pp.resize(e-pp.begin());
	for (auto &p:pp)
		cout << p << endl;
	return 0;
}
