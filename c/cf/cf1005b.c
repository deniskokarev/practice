#include <iostream>
#include <algorithm>
/* CodeForces CF1005B problem */
using namespace std;

int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1 >> s2;
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	int m;
	for (m=0; m<min(s1.length(), s2.length()) && s1[m] == s2[m]; m++);
	cout << (s1.length()+s2.length() - 2*m) << endl;
	return 0;
}
