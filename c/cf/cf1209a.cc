#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1209A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	for (auto &a:aa)
		cin >> a;
	sort(aa.begin(), aa.end());
	int ncol = 0;
	vector<int> col(n);
	for (int i=0; i<n; i++) {
		if (!col[i]) {
			ncol++;
			for (int j=i; j<n; j++)
				if (aa[j] % aa[i] == 0)
					col[j] = ncol;
		}
	}
	cout << ncol << endl;
	return 0;
}
