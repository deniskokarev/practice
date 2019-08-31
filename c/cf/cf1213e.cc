#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
/* CodeForces CF1213E problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s, t;
	cin >> n >> s >> t;
	vector<vector<int>> sp(3, vector<int>(3, 1));
	sp[s[0]-'a'][s[1]-'a'] = 0;
	sp[t[0]-'a'][t[1]-'a'] = 0;
	string ans(3*n, ' ');
	vector<int> path2 {0,1,2};
	// try to find aaa->bbb->ccc
	int l=0;
	while (l<6 &&
		   !(
			 sp[path2[0]][path2[0]] &&
			 sp[path2[0]][path2[1]] &&
			 sp[path2[1]][path2[1]] &&
			 sp[path2[1]][path2[2]] && 
			 sp[path2[2]][path2[2]])
		   )
	{
		next_permutation(path2.begin(), path2.end());
		l++;
	}
	if (l<6) {
		for (int i=0; i<3; i++)
			fill(ans.begin()+i*n, ans.begin()+(i+1)*n, path2[i]+'a');
	} else {
		// else try abcabc...
		for (l = 0; l<6; l++) {
			if (sp[path2[0]][path2[1]] && sp[path2[1]][path2[2]] && sp[path2[2]][path2[0]])
				break;
			next_permutation(path2.begin(), path2.end());
		}
		if (l<6) {
			for (int i=0; i<n; i++) {
				ans[3*i] = path2[0]+'a';
				ans[3*i+1] = path2[1]+'a';
				ans[3*i+2] = path2[2]+'a';
			}
		} else {
			assert(false && "should never happen");
		}
	}
	cout << "YES" << endl << ans << endl;
	return 0;
}
