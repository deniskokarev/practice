/* ACMP 1174 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	string s;
	cin >> n >> m >> s;
	int l = s.length()/m;
	map<string, vector<int>> mm;
	for (int i=0; i<m; i++) {
		string ms;
		cin >> ms;
		mm[ms].push_back(i);
	}
	for (int i=0; i<s.length()/l; i++) {
		string seg = s.substr(i*l, l);
		auto &vv = mm[seg];
		cout << vv.back()+1 << ' ';
		vv.pop_back();
	}
	cout << endl;
	return 0;
}
