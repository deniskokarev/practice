#include <iostream>
#include <algorithm>
/* CodeForces CF985A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int pp[n/2];
	for (auto &p:pp)
		cin >> p;
	sort(pp, pp+n/2);
	int f = 1;
	int ans_b = 0;
	for (auto &p:pp) {
		ans_b += abs(p-f);
		f += 2;
	}
	f = 2;
	int ans_w = 0;
	for (auto &p:pp) {
		ans_w += abs(p-f);
		f += 2;
	}
	cout << min(ans_b, ans_w) << endl;
	return 0;
}
