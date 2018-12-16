#include <iostream>
/* CodeForces CF1084C problem */
using namespace std;

constexpr int MOD = 1e9+7;

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sz = int(s.size());
	int ans[sz+1];
	ans[sz] = 0;
	int bi=sz;
	for (int i=sz-1; i>=0; i--) {
		ans[i] = ans[i+1];
		if (s[i] == 'a') {
			ans[i] += 1+ans[bi];
			ans[i] %= MOD;
		} else if (s[i] == 'b') {
			bi = i;
		}
	}
	cout << ans[0] << endl;
	return 0;
}
