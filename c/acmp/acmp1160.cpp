/* ACMP 1160 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int pp[s.size()+1];
	for (auto &p:pp)
		p = 0;
	for (int i=0; i<s.size(); i++) {
		if (pp[i] < i && s[pp[i]] == s[i])
			pp[i+1] = pp[i]+1;
		else
			pp[i+1] = 0;
	}
	for (int i=1; i<=s.size(); i++)
		cout << pp[i] << ' ';
	cout << endl;
	return 0;
}
