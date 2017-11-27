/* ACMP 1160 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int pp[s.size()]; // prefix fn
	fill(pp, pp+s.size(), 0);
	int k=0;
	for (int i=1; i<s.size(); i++) {
		if (i>k) {
			if (s[i] != s[k]) {
				while (k>0) {
					int j;
					for (j=0; j<k && s[i-j] == s[k-j-1]; j++);
					if (j == k)
						break;
					k--;
				}
				pp[i] = k;
			} else {
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
