/* ACMP 443 */
#include <iostream>
#include <algorithm>

using namespace std;

int myhash(const string &s, int m, int x) {
	int p = 1;
	int h = 0;
	for (auto c:s) {
		h += p*(c-'0');
		h %= m;
		p *= x;
		p %= m;
	}
	return h;
}

int main(int argc, char **argv) {
	int n, m, x;
	cin >> n >> m >> x;
	int hh[m];
	fill(hh, hh+m, 1);
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		hh[myhash(s, m, x)]++;
	}
	int a = 0;
	for (auto h:hh) {
		int cnt = h-1;
		a += cnt*(cnt-1)/2;
	}
	cout << a << endl;
	return 0;
}
