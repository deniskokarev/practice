/* ACMP 192 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int ss[n];
	for (auto &s:ss)
		cin >> s;
	next_permutation(ss, ss+n);
	for (auto &s:ss)
		cout << s << ' ';
	cout << endl;
	return 0;
}
