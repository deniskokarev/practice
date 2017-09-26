/* ACMP 401 */
#include <iostream>
#include <vector>

using namespace std;

uint64_t cnt(int n, int a, vector<vector<uint64_t>> &cache) {
	if (cache[n][a] == 0) {
		uint64_t s = 0;
		if (n>0)
			for (int i=0; i<=a; i++)
				s += cnt(n-1, i, cache);
		else
			s++;
		cache[n][a] = s;
	}
	return cache[n][a];
}

int main(int argc, char **argv) {
	int n, a, b;
	cin >> n >> a >> b;
	vector<vector<uint64_t>> cache(n+1, vector<uint64_t>(max(a,b)+1, 0));
	cout << cnt(n, a, cache) * cnt(n, b, cache) << endl;
	return 0;
}
