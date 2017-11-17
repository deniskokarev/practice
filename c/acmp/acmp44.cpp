/* ACMP 44 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	string aar[2] = {
		">>-->",
		"<--<<"
	};
	int ans = 0;
	for (auto &a:aar)
		for (size_t pos=pos=s.find(a); pos != string::npos; pos=s.find(a, pos+1))
			ans++;
	cout << ans << endl;
	return 0;
}
