/* ACMP 87 */
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	unordered_set<string> ss;
	vector<string> vss;
	string inps;
	while (getline(cin, inps)) {
		if (inps == "ENDOFINPUT")
			break;
		ss.insert(inps);
		vss.push_back(inps);
	}
	int ans = 0;
	for (auto &s:vss) {
		for (int i=1; i<s.length(); i++) {
			string l = s.substr(0, i);
			string r = s.substr(i, s.length()-i);
			if (ss.find(l) != ss.end() && ss.find(r) != ss.end()) {
				ans++;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
