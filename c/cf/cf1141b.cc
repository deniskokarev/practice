#include <iostream>
#include <vector>
/* CodeForces CF1141B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n+n);
	for (int i=0; i<n; i++)
		cin >> aa[i];
	copy(aa.begin(), aa.begin()+n, aa.begin()+n);
	int d1=0;
	int mx = 0;
	for (int j=n+n-1; j>=0; j--) {
		if (aa[j] == 0)
			d1 = j;
		else
			mx = max(mx, d1-j);
	}
	cout << mx << endl;
	return 0;
}
