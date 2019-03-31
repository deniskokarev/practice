#include <iostream>
#include <vector>
/* CodeForces CF1144D problem */
using namespace std;

constexpr int MX = 2e5+1;

struct OP {
	int i, j;
	int op;
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	vector<int> cnt(MX);
	int mxv = 0;
	for (auto &a:aa) {
		cin >> a;
		cnt[a]++;
		if (cnt[mxv] < cnt[a])
			mxv = a;
	}
	int fp;
	for (int j=n-1; j>=0; j--)
		if (aa[j] == mxv)
			fp = j;
	vector<OP> op;
	for (int j=fp; j>0; j--) {
		if (aa[j-1] > aa[j]) {
			op.push_back(OP {j-1, j, 2});
			aa[j-1] = aa[j];
		} else if (aa[j-1] < aa[j]) {
			op.push_back(OP {j-1, j, 1});
			aa[j-1] = aa[j];
		}
	}
	for (int j=fp; j<n-1; j++) {
		if (aa[j+1] > aa[j]) {
			op.push_back(OP {j+1, j, 2});
			aa[j+1] = aa[j];
		} else if (aa[j+1] < aa[j]) {
			op.push_back(OP {j+1, j, 1});
			aa[j+1] = aa[j];
		}
	}
	cout << op.size() << '\n';
	for (auto &o:op)
		cout << o.op << ' ' << o.i+1 << ' ' << o.j+1 << '\n';
	return 0;
}
