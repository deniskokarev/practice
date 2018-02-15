/* CodeForces CF919B problem */
#include <iostream>
#include <numeric>

using namespace std;

constexpr int SZ = 10;

bool dfs(int dd[SZ], int l, int &k, int sum) {
	if (l >= SZ) {
		if (sum == 10)
			k--;
		return (k == 0);
	}
	int ts = sum;
	for (dd[l]=0; dd[l]<SZ; dd[l]++) {
		if (ts > SZ)
			return false;
		if (dfs(dd, l+1, k, ts))
			return true;
		ts++;
	}
	return false;
}

int main(int argc, char **argv) {
	int k;
	cin >> k;
	int dd[SZ];
	if (dfs(dd, 0, k, 0)) {
		int i;
		for (i=0; i<SZ && dd[i]==0; i++);
		for (; i<SZ; i++)
			cout << dd[i];
	}
	cout << endl;
	return 0;
}
