/* ACMP 295 */
#include <iostream>

using namespace std;

constexpr unsigned mod = 'Z' - 'A' + 1;

int main(int argc, char **argv) {
	string e, s;
	cin >> e >> s;
	basic_string<unsigned> e_sq;
	basic_string<unsigned> s_sq;
	for (int i=0; i<s.size()-1; i++)
		s_sq.push_back((unsigned(s[i+1])+mod-unsigned(s[i]))%mod);
	for (int i=0; i<e.size()-1; i++)
		e_sq.push_back((unsigned(e[i+1])+mod-unsigned(e[i]))%mod);
	unsigned k = INT_MAX;
	bool match = false;
	for (size_t pos=e_sq.find(s_sq); pos != string::npos; pos=e_sq.find(s_sq, pos+1)) {
		match = true;
		unsigned nk = (unsigned(e[pos])+mod-unsigned(s[0]))%mod;
		//cerr << "pos: " << pos << " k: " << k << " nk: " << nk << endl;
		if (nk < k)
			k = nk;
	}
	k = (k + mod) % mod;
	if (match) {
		for (char &c:e)
			c = (unsigned(c)+mod-'A'-k)%mod + 'A';
		cout << e << endl;
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
