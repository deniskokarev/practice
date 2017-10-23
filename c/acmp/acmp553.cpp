/* ACMP 553 */
#include <iostream>
#include <vector>

using namespace std;

struct B {
	unsigned m, k;
	unsigned score;
	B operator+(const B&b) const {
		B r = {m, b.k, m * b.k + score + b.score};
		return r;
	}
	bool operator<(const B &b) const {
		return score < b.score;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<B>> bb(n+1, vector<B>(n+1));
	for (int i=0; i<n; i++) {
		unsigned m, k;
		cin >> m >> k;
		bb[i][i] = B {m, k, 0};
	}
	for (int l=1; l<n; l++) {
		for (int i=0; i<=n-l; i++) {
			B best = bb[i][i]+bb[i+1][i+l];
			for (int j=i+1; j<i+l; j++) {
				B curr = bb[i][j]+bb[j+1][i+l];
				if (curr < best)
					best = curr;
			}
			bb[i][i+l] = best;
		}
	}
	cout << bb[0][n-1].score << endl;
	return 0;
}
