/* ACMP 157 */
#include <iostream>

using namespace std;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int ll[256] = {0};
	for (auto c:s)
		ll[int(c)]++;
	uint64_t d = 1;
	for (auto l:ll)
		if (l)
			d *= fact(l);
	cout << fact(s.length())/d << endl;
	return 0;
}
