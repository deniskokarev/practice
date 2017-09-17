/* ACMP 500 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<pair<int,int>> aa(n); // age,risk
	for (auto &a:aa)
		cin >> a.first >> a.second;
	sort(aa.begin(), aa.end(), greater<pair<int,int>>());
	unsigned rr[3];
	rr[0] = 0;
	rr[1] = INT_MAX;
	int ri = 2;
	for (auto &a:aa) {
		rr[ri] = min(rr[(ri+3-2)%3]+a.second, rr[(ri+3-1)%3]+a.second);
		ri = (ri+1)%3;
	}
	cout << rr[n%3] << endl;
	return 0;
}
