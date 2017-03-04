#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF779C problem */
using namespace std;

struct D {
	int a;
	int b;
	int diff;
	D(){}
	D(int _a, int _b):a(_a),b(_b),diff(_a-_b){}
	bool operator<(const D &o) const {return diff<o.diff;}
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	vector<int> b(n);
	vector<D> d(n);
	for(int i=0; i<n; i++)
		cin >> a[i];
	for(int i=0; i<n; i++) {
		cin >> b[i];
		d[i] = D(a[i], b[i]);
	}
	sort(d.begin(), d.end());
	int64_t sum = 0;
	int i;
	for (i=0; i<k; i++)
		sum += d[i].a;
	for (; i<n && d[i].diff < 0; i++)
		sum += d[i].a;
	for (; i<n; i++)
		sum += d[i].b;
	cout << sum << endl;
	return 0;
}
