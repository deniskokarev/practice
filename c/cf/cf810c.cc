#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF810C problem */
using namespace std;

const int64_t mod = 1e9+7;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int64_t> x(n);
	for (int i=0; i<n; i++)
		cin >> x[i];
	sort(x.begin(), x.end());
	int64_t a = 0, p2m = 2, sp = 0, sm = 0;
	for (int i=n-2; i>=0; i--) {
		a = 2*a+x[i+1];
		sp += a;
		sm += (p2m-1)*x[i];
		p2m *= 2;
		a %= mod;
		sp %= mod;
		sm %= mod;
		p2m %= mod;
	}
	cout << (sp+mod-sm)%mod << endl;
	return 0;
}
