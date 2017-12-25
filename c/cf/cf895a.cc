#include <iostream>
/* CodeForces CF895A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int ss[n+1];
	ss[0] = 0;
	int sum = 0;
	for (int i=1; i<=n; i++) {
		cin >> ss[i];
		sum += ss[i];
	}
	for (int i=1; i<=n; i++)
		ss[i] += ss[i-1];
	int mn = INT_MAX;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<=n; j++) {
			int p1 = ss[j]-ss[i];
			int p2 = sum - p1;
			int diff = abs(p1-p2);
			mn = min(mn, diff);
		}
	}
	cout << mn << endl;
	return 0;
}
