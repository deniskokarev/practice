/* ACMP 1151 */
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	bool uc=false, lc=false, dc=false;
	for (auto c:s) {
		if (c>='a' && c<='z')
			lc = true;
		else if (c>='A' && c<='Z')
			uc = true;
		else if (c>='0' && c<='9')
			dc = true;
	}
	bool ans = (lc&&uc&&dc&&s.size()>=12); 
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
