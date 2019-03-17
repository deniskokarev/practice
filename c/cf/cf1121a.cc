#include <iostream>
#include <vector>
#include <tuple>
/* CodeForces CF1121A problem */
using namespace std;

using P = tuple<int,int,int>; // strength, sch, sel

int main(int argc, char **argv) {
	int n, m, k;
	cin >> n >> m >> k;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> get<0>(p);
	for (auto &p:pp) {
		cin >> get<1>(p);
		get<1>(p)--;
	}
	for (int i=0; i<k; i++) {
		int j;
		cin >> j;
		get<2>(pp[j-1]) = 1;
	}
	vector<int> ms(m, -1);
	for (int i=0; i<n; i++) {
		auto &p = pp[i];
		if (ms[get<1>(p)] == -1)
			ms[get<1>(p)] = i;
		else if (ms[get<1>(p)] < get<0>(p))
			ms[get<1>(p)] = i;
	}
	for (auto m:ms)
		get<2>(pp[m]) = 0;
	int ans = 0;
	for (auto &p:pp)
		ans += get<2>(p);
	cout << ans << endl;
	return 0;
}
