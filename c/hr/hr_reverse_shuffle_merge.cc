#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	unsigned sz = s.size();
	vector<array<int,26>> lcnt(sz+1, {{0}});
	vector<array<int,26>> lpos(sz+1, {{0}});
	for (unsigned i=1; i<=sz; i++) {
		lcnt[i] = lcnt[i-1];
		lcnt[i][s[i-1]-'a']++;
		lpos[i] = lpos[i-1];
		lpos[i][s[i-1]-'a'] = i;
	}
	array<int,26> need {{0}};
	for (unsigned char c:s)
		need[c-'a']++;
	for (int &n:need)
		n /= 2;
	string ans;
	int end = sz;
	while (ans.size() < sz/2) {
		for (int c=0; c<26; c++) {
			if (need[c]) {
				int pos = lpos[end][c];
				bool enough = true;
				for (int nc=0; nc<26; nc++)
					enough &= (need[nc] <= lcnt[pos][nc]);
				if (enough) {
					ans += c+'a';
					need[c]--;
					end = pos-1;
					break;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}

