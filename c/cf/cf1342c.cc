#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1342C problem */
using namespace std;

int main(int argc, char **argv) {
	int q;
	cin >> q;
	while (q--) {
		int a, b, q;
		cin >> a >> b >> q;
		int sz = a*b;
		vector<int> tt(sz+1);
		tt[0] = 0;
		for (int i=1; i<=sz; i++)
			tt[i] = tt[i-1] + (i%a%b == i%b%a);
		while (q--) {
			int64_t l, r;
			cin >> l >> r;
			int64_t cr = (r/sz)*tt[sz];
			cr += tt[r%sz];
			int64_t cl = ((l-1)/sz)*tt[sz];
			cl += tt[(l-1)%sz];
			cout << (r-l+1) - (cr-cl) << ' ';
		}
		cout << '\n';
	}
	return 0;
}
