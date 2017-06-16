#include <iostream>
#include <algorithm>
/* CodeForces CF814C problem */
using namespace std;

struct MXI {
	int b, e;
	int len() const {
		return e-b;
	}
	bool operator<(const MXI &z) const {
		return len()<z.len();
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	cin >> s;
	MXI mx['z'-'a'+1][n+1];	// per <= given m for all letters
	for (char l='a'; l<='z'; l++) {
		int li = l-'a';
		MXI mxm[n+1]; // per given m for letter l
		fill(mxm, mxm+n+1, MXI{0,0});
		int cnt[n+1];
		cnt[0] = 0;
		for (int i=0; i<n; i++) 
			cnt[i+1] = (s[i] == l)?(cnt[i]+1):(cnt[i]);
		for (int i=0; i<n; i++) {
			for (int j=i+1; j<=n; j++) {
				MXI mxi = {i, j};
				int c = cnt[j]-cnt[i];
				int m = mxi.len()-c;
				mxm[m] = max(mxm[m], mxi);
			}
		}
		mx[li][0] = mxm[0];
		for (int i=1; i<=n; i++)
			mx[li][i] = max(mx[li][i-1], mxm[i]);
	}
	int q;
	cin >> q;
	for (int i=0; i<q; i++) {
		int m;
		char c;
		string sc;
		cin >> m >> sc;
		c = sc[0];
		cout << mx[c-'a'][m].len() << endl;
	}
	return 0;
}
