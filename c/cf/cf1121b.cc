#include <iostream>
#include <map>
/* CodeForces CF1121B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	map<int64_t,int> mm;
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			mm[aa[i] + aa[j]]++;
	int mx = -1;
	for (auto m:mm)
		mx = max(mx, m.second);
	cout << mx << endl;
	return 0;
}
