/* ACMP 160 */
// @see explanation https://www.olympiads.ru/sng/16/index.shtml
#include <iostream>
#include <vector>

using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

/**
 * LCM(a, b) - least common multiple
 */
uint64_t lcm(uint64_t a, uint64_t b) {
	return a * (b / gcd(a, b));
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> pp(n);
	for (auto &p:pp) {
		cin >> p;
		p--;
	}
	vector<bool> visited(n, false);
	uint64_t ans = 1;
	for (int i=0; i<n; i++) {
		uint64_t cnt = 0;
		int node = i;
		while (!visited[node]) {
			visited[node] = true;
			node = pp[node];
			cnt++;
		}
		if (cnt > 0)
			ans = lcm(ans, cnt);
	}
	cout << ans << endl;
	return 0;
}
