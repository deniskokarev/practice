#include <iostream>
#include <vector>
/* ACMP 366 */
using namespace std;

static bool tryme(const vector<int> &aa, vector<int> &op, int pos, int res, int key) {
	if (pos < op.size()) {
		for (int o:{-1,1}) {
			op[pos] = o;
			if (tryme(aa, op, pos+1, res+aa[pos+1]*o, key))
				return true;
		}
		return false;
	} else {
		return res == key;
	}
}

int main(int argc, char **argv) {
	int n, s;
	cin >> n >> s;
	vector<int> aa(n);
	for (int i=0; i<n; i++)
		cin >> aa[i];
	vector<int> op(n-1);
	if (tryme(aa, op, 0, aa[0], s)) {
		int i = 0;
		cout << aa[i++];
		for (auto o:op) {
			cout << ((o==-1)?'-':'+');
			cout << aa[i++];
		}
		cout << '=' << s << endl;
	} else {
		cout << "No solution" << endl;
	}
	return 0;
}
