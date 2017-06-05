#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF770B problem */
using namespace std;

int sumd(const vector<int> &dd) {
	int sumd = 0;
	for (auto d:dd)
		sumd += d;
	return sumd;
}

int64_t num(const vector<int> &dd) {
	int64_t rc = 0;
	for (auto d:dd) {
		rc *= 10;
		rc += d;
	}
	return rc;
}

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	vector<int> dd;
	int64_t tn = n;
	while (tn > 0) {
		dd.push_back(tn%10);
		tn /= 10;
	}
	reverse(dd.begin(), dd.end());
	vector<int> mxdd(dd);
	for (int i=0; i<dd.size(); i++) {
		vector<int> tdd(dd);
		tdd[i]--;
		for (int j=i+1; j<dd.size(); j++)
			tdd[j] = 9;
		if (sumd(tdd) >= sumd(mxdd))
			mxdd = tdd;
	}
	if (sumd(dd) >= sumd(mxdd))
		mxdd = dd;
	cout << num(mxdd) << endl;
	return 0;
}
