#include <iostream>
#include <set>
#include <vector>
/* ACMP 91 */
using namespace std;

int main(int argc, char **argv) {
	set<int> aas;
	vector<int> aa(100001);
	vector<int> bb(100001);
	aa[0] = 2;
	aa[1] = 3;
	aa[2] = 4;
	aa[3] = 7;
	aa[4] = 13;
	aa[5] = 15;
	aas.insert(2);
	aas.insert(3);
	aas.insert(4);
	aas.insert(7);
	aas.insert(13);
	aas.insert(15);
	bb[0] = 1;
	bb[1] = 5;
	bb[2] = 6;
	bb[3] = 8;
	bb[4] = 9;
	bb[5] = 10;
	for (int k = 6; k<aa.size(); k++) {
		aa[k] = bb[k-1]+bb[k-3];
		aas.insert(aa[k]);
		int i;
		for (i=bb[k-1]+1; aas.find(i) != aas.end(); i++);
		bb[k] = i;
	}
	int n;
	cin >> n;
	n--;
	cout << aa[n] << endl;
	cout << bb[n] << endl;
	return 0;
}
