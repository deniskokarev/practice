#include <iostream>
#include <vector>
/* ACMP 356 */
using namespace std;

constexpr int MXW = 1e4+1;

int main(int argc, char **argv) {
	int e, f;
	cin >> e >> f;
	int n;
	cin >> n;
	int pp[n], ww[n];
	for (int i=0; i<n; i++)
		cin >> pp[i] >> ww[i];
	vector<int> dyn_mx(MXW*2, INT_MIN), dyn_mn(MXW*2, INT_MAX/2);
	dyn_mx[MXW] = dyn_mn[MXW] = 0;
	for (int w=MXW; w<MXW*2; w++) {
		for (int i=0; i<n; i++) {
			dyn_mx[w] = max(dyn_mx[w], dyn_mx[w-ww[i]]+pp[i]);
			dyn_mn[w] = min(dyn_mn[w], dyn_mn[w-ww[i]]+pp[i]);
		}
	}
	int mx = dyn_mx[MXW+f-e];
	int mn = dyn_mn[MXW+f-e];
	if (mx > 0)
		cout << mn << ' ' << mx << endl;
	else
		cout << "This is impossible." << endl;
	return 0;
}
