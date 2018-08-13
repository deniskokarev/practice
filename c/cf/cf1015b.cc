#include <iostream>
#include <vector>
/* CodeForces CF1015B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	string s, t;
	cin >> n >> s >> t;
	vector<int> ans;
	for (int i=0; i<n; i++) {
		int j;
		for (j=i; j<n; j++) {
			if (t[i] == s[j]) {
				for (int k=j; k>i; k--) {
					ans.push_back(k);
					swap(s[k-1],s[k]);
				}
				break;
			}
		}
		if (j==n)
			goto no_ans;
	}
	cout << ans.size() << endl;
	for (auto a:ans)
		cout << a << ' ';
	cout << endl;
	return 0;
 no_ans:
	cout << -1 << endl;
	return 0;
}
