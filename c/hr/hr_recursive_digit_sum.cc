// https://www.hackerrank.com/challenges/recursive-digit-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=recursion-backtracking
#include <iostream>
#include <vector>

using namespace std;

int dig_sum(int64_t n) {
	string sn = to_string(n);
	int sm = 0;
	for (auto c:sn)
		sm += c-'0';
	if (sm > 9)
		return dig_sum(sm);
	else
		return sm;
}

int main(int argc, char **argv) {
	string sn;
	int64_t k;
	cin >> sn >> k;
	int sm = 0;
	for (auto c:sn)
		sm += c-'0';
	cout << dig_sum(sm * k) << endl;
	return 0;
}

