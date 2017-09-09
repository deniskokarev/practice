/* ACMP 1174 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv) {
	int n, m;
	string s;
	cin >> n >> m >> s;
	int l = s.length()/m;
	multimap<string, int> mm;
	for (int i=0; i<m; i++) {
		string ms;
		cin >> ms;
		mm.emplace(ms, i);
	}
	for (int i=0; i<s.length()/l; i++) {
		string seg = s.substr(i*l, l);
		auto mel = mm.find(seg);
		cout << mel->second+1 << ' ';
		mm.erase(mel);
	}
	cout << endl;
	return 0;
}
