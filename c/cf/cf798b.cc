#include <iostream>
#include <vector>

/* CodeForces CF798B problem */
using namespace std;

// transform a->b
int diff(const string &a, const string &b) {
	if (a.length() != b.length())
		return -1;
	int l = a.length();
	for (int i=0; i<l; i++) {
		for (int j=0; j<l; j++) {
			int n;
			for (n=0; n<l && a[(i+n)%l]==b[(j+n)%l]; n++);
			if (n == l)
				return j; 
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<string> ss(n);
	for (auto &s:ss)
		cin >> s;
	int mn = INT_MAX;
	for (int i=0; i<n; i++) {
		int sum = 0;
		for (int j=0; j<n; j++) {
			int d = diff(ss[i], ss[j]);
			if (d < 0) {
				cout << -1 << endl;
				return 0;
			}
			sum += d;
		}
		mn = min(mn, sum);
	}
	cout << mn << endl;
	return 0;
}
