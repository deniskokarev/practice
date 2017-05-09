#include <iostream>
/* CodeForces CF805B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	string pat("abba");
	for (int i=0; i<n; i++)
		s += pat[i%pat.size()];
	cout << s << endl;
	return 0;
}
