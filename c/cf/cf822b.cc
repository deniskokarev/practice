#include <iostream>
/* CodeForces CF822B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	string s, t;
	cin >> n >> m >> s >> t;
	int mn = INT_MAX;
	int pos = -1;
	for (int i=0; i<=t.length()-s.length(); i++) {
		int neg = 0;
		for (int j=0; j<s.length(); j++)
			if (s[j]!=t[i+j])
				neg++;
		if (mn > neg) {
			mn = neg;
			pos = i;
		}
	}
	cout << mn << endl;
	for (int j=0; j<s.length(); j++)
		if (s[j]!=t[pos+j])
			cout << j+1 << ' ';
	cout << endl;
	return 0;
}
