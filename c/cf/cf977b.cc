#include <iostream>
#include <map>
/* CodeForces CF977B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s;
	cin >> n >> s;
	map<string,int> cnt;
	for (int i=0;i<s.length()-1;i++)
		cnt[s.substr(i,2)]++;
	int mx = 0;
	string ans;
	for (auto &p:cnt) {
		if (p.second > mx) {
			ans = p.first;
			mx = p.second;
		}
	}
	cout << ans << endl;
	return 0;
}
