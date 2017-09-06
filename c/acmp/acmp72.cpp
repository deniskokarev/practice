/* ACMP 72 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	next_permutation(s.begin(), s.end());
	cout << s << endl;
	return 0;
}
