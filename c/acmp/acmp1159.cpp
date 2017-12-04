/* ACMP 1159 */
#include <iostream>
#include <numeric>

using namespace std;

// palindrome finding code in O(n)
// taken from e-maxx forum
// NB! the code at the article http://e-maxx.ru/algo/palindromes_count
// is incorrect
void manacher(string s, int *d1, int *d2) {
	int n = s.length();
	int l=0, r=-1;
	for(int i = 0; i < n; i++) {
		int k;
		if (i > r)
			k = 1;
		else
			k = min(d1[l + r - i], r - i);
		while(0 <= i-k && i+k < n && s[i - k] == s[i + k])
			k++;
		d1[i] = k;
		if (i + k - 1 > r)
			r = i + k - 1, l = i - k + 1;
	}
	l=0, r=-1;
	for(int i = 0; i < n; i++){
		int k;
		if (i > r)
			k = 0;
		else
			k = min(d2[l + r - i + 1], r - i + 1);
		while (i + k < n && i - k - 1 >= 0 && s[i+k] == s[i - k - 1])
			k++;
		d2[i] = k;
		if (i + k - 1 > r)
			l = i - k, r = i + k - 1;
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
