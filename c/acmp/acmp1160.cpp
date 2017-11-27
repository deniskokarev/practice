/* ACMP 1160 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int pp[s.size()]; // prefix function
	fill(pp, pp+s.size(), 0);
	int k=0;
	for (int i=1; i<s.size(); i++) {
		if (i>k) {
			for (; k>0 && s[i] != s[k]; k=pp[k-1]);
			if (s[i] == s[k]) {
				k++;
				pp[i] = k;
			}
		}
	}
	for (int i=0; i<s.size(); i++)
		cout << pp[i] << ' ';
	cout << endl;
	return 0;
}
