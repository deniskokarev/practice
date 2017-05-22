#include <iostream>
#include <algorithm>
/* CodeForces CF801A problem */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int64_t n = 0;
	for (int i=1; i<s.length(); i++) {
		if (s[i-1] == 'V' && s[i] == 'K') {
			n++;
			s[i-1] = s[i] = ' ';
		}
	}
	for (int i=1; i<s.length(); i++) {
		if (s[i-1] == 'V' && s[i] == 'V' ||
			s[i-1] == 'K' && s[i] == 'K') {
			n++;
			break;
		}
	}
	cout << n << endl;
	return 0;
}
