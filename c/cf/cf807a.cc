#include <iostream>
/* CodeForces CF807A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int pj = INT_MAX;
	bool is_srt = true;
	bool is_diff = false;
	do {
		int i, j;
		cin >> i >> j;
		if (i != j) {
			is_diff = true;
		} else if (j > pj) {
			is_srt = false;
		}
		pj = j;
		n--;
	} while (n>0);
	if (is_diff) {
		cout << "rated";
	} else if (is_srt) {
		cout << "maybe";
	} else {	
		cout << "unrated";
	}
	cout << endl;
	return 0;
}
