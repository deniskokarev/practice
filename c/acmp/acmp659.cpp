/* ACMP 659 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

using BITS = bitset<32>; // 64 would'be been too slow

struct SEL_CTX {
	const vector<BITS> &ff;
	const int n;
	int mx;
	BITS mx_sel;
	BITS sel;
};

void choose_team(int k, int f, SEL_CTX &sc) {
	if (k>0) {
		for (int i=f; i<sc.n; i++) {
			sc.sel[i] = 1;
			choose_team(k-1, i+1, sc);
			sc.sel[i] = 0;
		}
	} else {
		int ft = 0; // friends in this team
		int fo = 0; // friends in other team
		for (int i=0; i<sc.n; i++) {
			if (sc.sel[i]) {
				BITS b = sc.ff[i];
				b &= sc.sel;
				ft += b.count();
			} else {
				BITS b = sc.ff[i];
				b &= ~sc.sel;
				fo += b.count();
			}
		}
		int f_tot = ft+fo;
		if (f_tot >= sc.mx) {
			sc.mx_sel = sc.sel;
			sc.mx = f_tot;
		}
	}
}
 
int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	vector<BITS> ff(n);
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		int mn_v = min(v1, v2);
		int mx_v = max(v1, v2);
		ff[mn_v].set(mx_v);
	}
	SEL_CTX sc {ff, n, 0, {0}, {0}};
	choose_team(k, 0, sc);
	for (int p=0; p<n; p++)
		if (sc.mx_sel[p])
			cout << p+1 << ' ';
	cout << endl;
	return 0;
}
