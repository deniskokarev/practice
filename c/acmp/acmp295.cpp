/* ACMP 295 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string e, s;
	cin >> e >> s;
	string e_sq(e);
	string s_sq(s);
	int mod = 'Z' - 'A' + 1;
	for (int i=0; i<s.size()-1; i++)
		s_sq[i] = ((int(s[i+1])-'A')+mod-(s[i]-'A'))%mod;
	s_sq.resize(s_sq.size()-1);
	for (int i=0; i<e.size()-1; i++)
		e_sq[i] = ((int(e[i+1])-'A')+mod-(e[i]-'A'))%mod;
	e_sq.resize(e_sq.size()-1);
	int k = INT_MAX;
	for (size_t pos=e_sq.find(s_sq); pos != string::npos; pos=e_sq.find(s_sq, pos+1)) {
		k = min(k, (int(s[0])+mod-e[pos])%mod);
		//cerr << "pos: " << pos << " k: " << k << endl;
	}
	if (k < INT_MAX) {
		for (auto &c:e)
			c = (int(c)-'A'+k)%mod + 'A';
		cout << e << endl;
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
