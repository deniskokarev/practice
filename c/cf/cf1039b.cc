#include <iostream>
#include <random>
/* CodeForces CF139B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	bool ans = false;
	mt19937 rnd(0);
	string s;
	int cnt = 0;
	int f = 1, t = n+1;
	while (!ans && cnt < 4500) {
		while (f+4*k<t) {
			int m=f+(t-f)/2;
			cnt++;
			cout << f << " " << m << endl;
			cin >> s;
			if (s == "Yes")
				t = min(n+1, m+k);
			else
				f = max(1, m-k+1);
		}
		cnt++;
		f = max(1, f-k);
		t = min(n+1, t+k);
		if (t>f) {
			unsigned pos = f+(rnd()%(t-f));
			cout << pos << " " << pos << endl;
		} else {
			cout << f << " " << f << endl;
		}
		cin >> s;
		ans = (s == "Yes");
	}
	return 0;
}
