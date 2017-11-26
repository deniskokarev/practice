/* ACMP 491 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sz = s.size();
	int l = sz;
	int j;
	for (j=0; j<sz/2 && s[j] == s[sz-j-1]; j++);
	if (j == sz/2)
		for (l=sz-1; l>1 && s[l] == s[l-1]; l--);
	//cerr << "j: " << j << " l: " << l << endl;
	if (l>1)
		cout << s.substr(0, l) << endl;
	else
		cout << "NO SOLUTION" << endl;
	return 0;
}
