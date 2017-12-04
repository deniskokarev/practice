/* ACMP 1159 */
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

// taken from e-maxx forum
// NB! the code at http://e-maxx.ru/algo/palindromes_count
// is incorrect
void manacher(string s, int *d1, int *d2) {
	int n = s.length();
	int *d[2] = {d1, d2};
	for (int p = 0; p < 2; ++p) {
		int l = 0, r = -1;
		for (int i = 0; i < n; ++i) {
			int k = (i > r ? 0 : min(d[p][l + r - i] - p, r - i)) + 1;
			while (i + k - 1 < n && i - k + p >= 0 && s[i + k - 1] == s[i - k + p]) ++k;
			d[p][i] = --k;
			if (i + k > r)
				l = i - k + p, r = i + k - 1;
		}
	}
}

void naive(string s, int *d1, int *d2) {
	int n = s.length();
	for (int i=0; i<n; ++i) {
		d1[i] = 1;
		while (i-d1[i] >= 0 && i+d1[i] < n && s[i-d1[i]] == s[i+d1[i]])
			++d1[i];
 
		d2[i] = 0;
		while (i-d2[i]-1 >= 0 && i+d2[i] < n && s[i-d2[i]-1] == s[i+d2[i]])
			++d2[i];
	}
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	size_t len = s.length();
	int d1[len], d2[len];
#if 1
	manacher(s, d1, d2);
#else	
	naive(s, d1, d2);
#endif
	uint64_t ans = accumulate(d1, d1+len, 0ULL);
	ans += accumulate(d2, d2+len, 0ULL);
	cout << ans << endl;
	return 0;
}
