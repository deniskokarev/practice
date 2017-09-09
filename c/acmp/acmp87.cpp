/* ACMP 87 */
#include <iostream>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {
	unordered_set<string> ss;
	string s;
	while (getline(cin, s)) {
		if (s == "ENDOFINPUT")
			break;
		ss.insert(s);
	}
	int ans = 0;
	for (auto &s:ss) {
		for (int i=1; i<s.length()-1; i++) {
			string l = s.substr(0, i);
			string r = s.substr(i, s.length()-i);
			if (ss.find(l) != ss.end() && ss.find(r) != ss.end())
				ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
