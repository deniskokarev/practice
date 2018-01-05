/* ACMP 1205 */
#include <iostream>
#include <sstream>
#include <numeric>
#include <iterator>

using namespace std;

int sumline(const string &s) {
	istringstream iss(s);
	return accumulate(istream_iterator<int>(iss), istream_iterator<int>(), 0);
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	getline(cin, s);
	getline(cin, s);
	int fs = sumline(s);
	bool ans = true;
	n--;
	while (n-- > 0) {
		getline(cin, s);
		ans &= (fs == sumline(s));
	}
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
