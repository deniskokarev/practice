#include <iostream>
#include <algorithm>
/* CodeForces CF999B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s;
	cin >> n;
	cin >> s;
	for (int i=1; i<=n; i++) {
		if (n%i == 0)
			reverse(s.begin(), s.begin()+i);
	}
	cout << s << endl;
	return 0;
}
