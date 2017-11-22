/* ACMP 295 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string e, s;
	cin >> e >> s;
	basic_string<uint8_t> e_sq;
	basic_string<uint8_t> s_sq;
	int mod = 'Z' - 'A' + 1;
	for (int i=0; i<s.size()-1; i++)
		s_sq.push_back(((int(s[i+1]))-int(s[i])+mod)%mod);
	for (int i=0; i<e.size()-1; i++)
		e_sq.push_back(((int(e[i+1]))-int(e[i])+mod)%mod);
	int k = INT_MAX;
	for (size_t pos=e_sq.find(s_sq); pos != string::npos; pos=e_sq.find(s_sq, pos+1)) {
		k = min(k, (int(s[0])-int(e[pos])+mod)%mod);
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
