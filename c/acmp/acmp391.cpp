/* ACMP 391 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int polyhash(const vector<int> &s, int mask, int x) {
	int p = 1;
	int h = 0;
	for (auto c:s) {
		h += p*c;
		h &= mask;
		p *= x;
		p &= mask;
	}
	return h;
}

string conv(const vector<int> &v) {
	string o(v.size(), ' ');
	for (int i=0; i<o.size(); i++)
		o[i] = v[i] + '0';
	return o;
}

int main(int argc, char **argv) {
	int x, m, l, v;
	cin >> x >> m >> l >> v;
	assert(((m-1)&m) == 0); // m is pow of 2
	int mask = m-1;
	vector<int> s(l, 0);
	int k;
	for (k=0; k<v*x && polyhash(s, mask, x) != v; k++) {
		for (int i=0; i<s.size(); i++) {
			if (s[i] < 9) {
				s[i]++;
				break;
			} else {
				s[i] = 0;
			}
		}
		//cerr << "s: " << conv(s) << " hash: " << polyhash(s, mask, x) << endl;
	}
	if (polyhash(s, mask, x) == v)
		cout << conv(s) << endl;
	else
		cout << "NO SOLUTION" << endl;
	return 0;
}
