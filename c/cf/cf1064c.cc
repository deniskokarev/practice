#include <iostream>
#include <algorithm>
/* CodeForces CF1064C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	cin >> s;
	sort(s.begin(), s.end());
	cout << s << endl;
	return 0;
}
