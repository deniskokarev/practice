#include <iostream>
#include <vector>
/* ACMP 588 problem */
using namespace std;

int main(int argc, char **argv) {
	// very non-trivial constructive
	// b >= 7 number has a certain pattern 
	int b;
	cin >> b;
	vector<int> n(b+1, 0);
	bool ans = true;
	if (b < 4) {
		ans = false;
	} else if (b == 6) {
		ans = false;
	} else if (b == 4) {
		n[1] = 2; n[2] = 1; n[b] = 1;
	} else if (b == 5) {
		n[1] = 1; n[2] = 2; n[b] = 2;
	} else {
		n[1] = 2;
		n[2] = 1;
		n[b - 4] = 1;
		n[b] = b - 4;
	}
	if (ans)
		for (int i=1; i<n.size(); i++)
			cout << n[i] << endl;
	else
		cout << -1 << endl;
	return 0;
}
