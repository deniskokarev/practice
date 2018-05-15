#include <iostream>
/* CodeForces CF976A problem */
using namespace std;

int main(int argc, char **argv) {
	int ignore;
	cin >> ignore;
	string s;
	cin >> s;
	int cnt[2]{0};
	for (auto c:s)
		cnt[c-'0']++;
	if (cnt[1] > 0) {
		cout << '1';
		for (int i=0; i<cnt[0]; i++)
			cout << '0';
	} else {
		cout << '0';
	}
	cout << endl;
	return 0;
}
