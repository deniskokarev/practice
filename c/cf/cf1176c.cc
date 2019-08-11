#include <iostream>
/* CodeForces CF1176C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int nseq[7]{};
	int rm = 0;
	const int seq[7] = {0, 4, 8, 15, 16, 23, 42};
	nseq[0] = INT_MAX;
	while (n--) {
		int a;
		cin >> a;
		for (int i=1; i<7; i++) {
			if (seq[i] == a && nseq[i-1] > 0) {
				nseq[i-1]--;
				nseq[i]++;
				goto nxt;
			}
		}
		rm++;
	nxt:
		;
	}
	//cerr << "rm=" << rm << endl;
	for (int i=1; i<6; i++) {
		//cerr << "i=" << i << " nseq=" << nseq[i] << endl;
		rm += nseq[i]*i;
	}
	cout << rm << endl;
	return 0;
}
