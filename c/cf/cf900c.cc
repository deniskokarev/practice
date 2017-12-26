#include <iostream>
#include <algorithm>

/* CodeForces CF900C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int mx[n][2]; // 2 max elements to the left
	mx[0][0] = aa[0];
	mx[0][1] = -1;
	for (int i=1; i<n; i++) {
		if (aa[i] < mx[i-1][1]) {
			mx[i][1] = mx[i-1][1];
			mx[i][0] = mx[i-1][0];
		} else if (aa[i] < mx[i-1][0]) {
			mx[i][1] = aa[i];
			mx[i][0] = mx[i-1][0];
		} else {
			mx[i][1] = mx[i-1][0];
			mx[i][0] = aa[i];
		}
	}
#if 0
	for (int i=0; i<n; i++)
		cerr << "mx0: " << mx[i][0] << " mx1: " << mx[i][1] << endl;
#endif
	int recmx[n+1];
	fill(recmx, recmx+n+1, 0);
	for (int i=1; i<n; i++)
		if (mx[i-1][0]>aa[i] && mx[i-1][1]<aa[i])
			recmx[mx[i-1][0]]++;
	auto me = max_element(recmx+1, recmx+n+1);
	cout << (me - recmx) << endl;
	return 0;
}
