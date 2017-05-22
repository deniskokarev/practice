#include <iostream>
#include <vector>
#include <map>

/* CodeForces 782A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	map<int, int> mm;
	int sum = 0;
	int mx = 0;
	for (int i=0; i<2*n; i++) {
		int x;
		cin >> x;
		if (mm[x] == 0) {
			sum++;
		} else if (mm[x] == 1) {
			sum--;
		}
		++mm[x];
		mx = max(sum, mx);
	}
	cout << mx <<endl;
	return 0;
}
