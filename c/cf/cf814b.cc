#include <iostream>
#include <algorithm>
/* CodeForces CF814B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int bb[n];
	for (auto &b:bb)
		cin >> b;
	int k = 0;
	int aan[n+1];
	fill(aan, aan+n+1, 0);
	for (int i=0; i<n; i++) {
		if (aa[i] != bb[i])
			k++;
		aan[aa[i]]++;
	}
	int miss;
	for (int i=1; i<=n; i++)
		if (aan[i] == 0)
			miss = i;
	if (k > 1) {
		for (int i=0; i<n; i++) {
			if (aa[i] != bb[i] && aan[aa[i]] > 1 && bb[i] == miss) {
				aa[i] = miss;
				break;
			}
		}
	} else {
		for (int i=0; i<n; i++) {
			if (aa[i] != bb[i]) {
				aa[i] = miss;
				break;
			}
		}
	}
 	for (auto &a:aa)
		cout << a << ' ';
	cout << endl;
	return 0;
}
