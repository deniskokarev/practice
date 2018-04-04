#include <iostream>
/* CodeForces CF955B problem */
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int cc[256] {0};
	for (auto c:s) {
		int idx = (unsigned char)c;
		cc[idx]++;
	}
	bool ans = false;
	int ss[256];
	int sscnt = 0;
	for (int i=0; i<256; i++)
		if (cc[i] > 0)
			ss[sscnt++] = cc[i];
	if (sscnt > 1 && sscnt < 5) {
		if (sscnt == 2) {
			ans = ss[0] > 1 && ss[1] > 1;
		} else if (sscnt == 3) {
			ans = ss[0] > 1 || ss[1] > 1 || ss[2] > 1;
		} else {
			ans = true;
		}
	}
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
