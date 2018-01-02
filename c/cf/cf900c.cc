#include <iostream>
#include <algorithm>

/* CodeForces CF900C problem */
using namespace std;

int fw_sum(int *fw, int p) {
	int s = 0;
	for (; p>=0; p=(p&(p+1))-1)
		s += fw[p];
	return s;
}

void fw_inc(int *fw, int p, int sz) {
	for (; p<sz; p|=(p+1))
		fw[p]++;
}

#define dim(X)	(int(sizeof(X)/sizeof(X[0])))

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int stat[n+1]; // contibutions/losses to the record
	fill(stat, stat+dim(stat), 0);
	int fw[n+1]; // number of less than current
	fill(fw, fw+dim(fw), 0);
	int mx = INT_MIN;
	for (int i=0; i<n; i++) {
		int cnt = fw_sum(fw, aa[i]-1);
		int gr = i-cnt;
		if (gr == 1)
			stat[mx]--;
		else if (gr == 0)
			stat[aa[i]]++;
		fw_inc(fw, aa[i], dim(fw));
		mx = max(mx, aa[i]);
	}
	auto e = min_element(stat+1, stat+dim(stat));
	cout << e-stat << endl;
	return 0;
}
