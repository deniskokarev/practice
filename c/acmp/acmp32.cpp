/* ACMP 32 */
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int getmm(int n, int mm) {
	char s[11];
	int sig = (n > 0) - (n < 0);
	int sz = snprintf(s, sizeof(s), "%d", n*sig);
	if (sig * mm >= 0) {
		sort(s, s+sz, less<char>());
		for (int i=0; s[0] == '0' && i<sz; i++)
			swap(s[0], s[i]);
	} else {
		sort(s, s+sz, greater<char>());
	}
	int res;
	sscanf(s, "%d", &res);
	return res*sig;
}

enum {
	MN = 1,
	MX = -1
};

int main() {
	int a, b;
	cin >> a >> b;
	cout << getmm(a, MX) - getmm(b, MN) << endl;
}

