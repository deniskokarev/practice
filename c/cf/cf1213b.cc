#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1213B problem */
using namespace std;

void fw_inc(int *fw, int fw_sz, int x, int d) {
        for (int i=x; i<fw_sz; i|=i+1)
                fw[i] += d;;
}

int fw_sum(const int *fw, int x) {
        int s = 0;
        for (int i=x; i>=0; i=(i&(i+1))-1)
                s += fw[i];
        return s;
}

constexpr int MX = 1e6+1;

int fw[MX];

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> aa(n);
		for (auto &a:aa)
			cin >> a;
		int cnt = 0;
		for (int i=aa.size()-1; i>=0; i--) {
			cnt += (fw_sum(fw, aa[i]-1) > 0);
			fw_inc(fw, MX, aa[i], +1);
		}
		for (auto &a:aa)
			fw_inc(fw, MX, a, -1);
		cout << cnt << "\n";
	}
	return 0;
}
