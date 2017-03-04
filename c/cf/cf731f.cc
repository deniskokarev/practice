#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF731F problem */
using namespace std;

int main(int argc, char **argv) {
	const int maxa = 200001;
	int n;
	cin >> n;
	vector<int> aa(n);
	for (int i=0; i<n; i++) {
		cin >> aa[i];
		aa[i] = aa[i]%maxa;
	}
	sort(aa.begin(), aa.end());
	vector<int> ss(maxa);
	for (int i=0; i<n; i++)
		ss[aa[i]]++;
	for (int i=0; i<maxa; i++)
		ss[i] += ss[i-1];
	int64_t mx = 0;
	auto it = unique(aa.begin(), aa.end());
	aa.resize(distance(aa.begin(), it));
	for (auto a:aa) {
		int64_t sum = 0;
		for (int n=1; a*n < maxa; n++) {
			int t = min(a*(n+1)-1, maxa-1);
			int f = a*n-1;
			sum += (int64_t)(ss[t]-ss[f])*a*n;
		}
		mx = max(mx, sum);
	}
	cout << mx << endl;
	return 0;
}
