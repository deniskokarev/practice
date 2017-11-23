/* ACMP 295 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string e, s;
	cin >> e >> s;
	basic_string<int> e_sq;
	basic_string<int> s_sq;
	for (int i=0; i<s.size()-1; i++)
		s_sq.push_back((int(s[i+1])-int(s[i])));
	for (int i=0; i<e.size()-1; i++)
		e_sq.push_back((int(e[i+1])-int(e[i])));
	int k = INT_MIN;
	bool match = false;
	for (size_t pos=e_sq.find(s_sq); pos != string::npos; pos=e_sq.find(s_sq, pos+1)) {
		match = true;
		int nk = (int(s[0])-int(e[pos]));
		if (abs(k)<abs(nk))
			k = nk;
		//cerr << "pos: " << pos << " k: " << k << endl;
	}
	if (match) {
		for (auto &c:e)
			c = int(c)+k;
		cout << e << endl;
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
