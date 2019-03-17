#include <iostream>
#include <vector>
#include <tuple>
/* CodeForces CF1121A problem */
using namespace std;

struct P {
	int strength;
	int school;
	int sel;
};

int main(int argc, char **argv) {
	int n, m, k;
	cin >> n >> m >> k;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.strength;
	vector<int> ms(m, -1);
	for (int i=0; i<n; i++) {
		int school;
		cin >> school;
		school--;
		if (ms[school] < 0 || pp[ms[school]].strength < pp[i].strength)
			ms[school] = i;
		pp[i].school = school;
	}
	int ans = 0;
	for (int i=0; i<k; i++) {
		int sel;
		cin >> sel;
		sel--;
		int school = pp[sel].school;
		ans += (ms[school] != sel);
	}
	cout << ans << endl;
	return 0;
}
