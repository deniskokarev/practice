#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1027A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		vector<vector<char>> ee(s.length(), vector<char>());
		for (int i=0; i<s.length(); i++) {
			for (int j:{-1,+1})
				if (s[i]+j >= 'a' && s[i]+j<='z')
					ee[i].push_back(s[i]+j);
		}
		bool ans = true;
		for (int i=0, j=ee.size()-1; i<ee.size()/2; i++,j--) {
			vector<char> u(3);
			int sz = set_intersection(ee[i].begin(), ee[i].end(), ee[j].begin(), ee[j].end(), u.begin()) - u.begin();
			ans &= (sz>0);
		}
		cout << ((ans)?"YES":"NO") << endl;
	}
	return 0;
}
