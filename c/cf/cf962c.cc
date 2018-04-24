#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <cassert>
/* CodeForces CF962C problem */
using namespace std;

int main(int argc, char **argv) {
	string sn;
	cin >> sn;
	reverse(sn.begin(), sn.end());
	int l10 = sn.length();
	assert(l10<=10);
	int mn = INT_MAX;
	for (int i=1; i<(1<<l10); i++) {
		bitset<10> bs(i);
		int num = 0;
		int p = 1;
		int drop = 0;
		char hi_dig = ' ';
		for (int i=0; i<l10; i++) {
			if (bs[i]) {
				num += (sn[i]-'0')*p;
				p*=10;
				hi_dig = sn[i];
			} else {
				drop++;
			}
		}
		if (hi_dig != '0') {
			int sq = floor(sqrt(num));
			if (sq*sq == num) {
				cerr << "num=" << num << " sq= " << sq << " bs=" << bs << " drop=" << drop << endl;
				mn = min(mn, drop);
			}
		}
	}
	if (mn  == INT_MAX)
		cout << "-1" << endl;
	else
		cout << mn << endl;
	return 0;
}
