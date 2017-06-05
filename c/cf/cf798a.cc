#include <iostream>
/* CodeForces CF798A problem */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int len = s.length();
	int cnt = 0;
	for (int i=0; i<len/2; i++) {
		if (s[i] != s[len-i-1])
			cnt++;
	}
	if (cnt == 0 && len%2 == 1)
		cnt++;
	cout << ((cnt==1)?"YES":"NO") << endl;
	return 0;
}
