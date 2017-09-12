/* ACMP 50 */
#include <iostream>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {
	string s, b;
	cin >> s >> b;
	unordered_set<string> bb;
	for (int i=0; i<b.length(); i++) {
		string a = b.substr(i, b.length()-i);
		a += b.substr(0, i);
		//cerr << a << endl;
		bb.insert(a);
	}
	int ans = 0;
	for (int i=0; i<=s.length()-b.length(); i++) {
		string a = s.substr(i, b.length());
		if (bb.find(a) != bb.end())
			ans++;
	}
	cout << ans << endl;
	return 0;
}
