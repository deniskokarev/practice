/* ACMP 994 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1 >> s2;
	/* matrix a-la max substring */
	/* left->right */
	vector<vector<uint16_t>> ss(s1.length()+2, vector<uint16_t>(s2.length()+2, 0));
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			if (s1[i-1] == s2[j-1])
				ss[i][j] = ss[i-1][j-1]+1;
	vector<uint16_t> mxl(s1.length()+2, 0);
	/* max from left */
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			mxl[i] = max(mxl[i], ss[i][j]);
	for (int i=1; i<=s1.length(); i++)
		mxl[i] = max(mxl[i], mxl[i-1]);
	/* right->left */
	for (auto &i : ss)
		fill(i.begin(), i.end(), 0);
	for (int i=s1.length(); i>=1; i--)
		for (int j=s2.length(); j>=1; j--)
			if (s1[i-1] == s2[j-1])
				ss[i][j] = ss[i+1][j+1]+1;
	/* max from right */
	vector<uint16_t> mxr(s1.length()+2, 0);
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			mxr[i] = max(mxr[i], ss[i][j]);
	for (int i=s1.length(); i>=1; i--)
		mxr[i] = max(mxr[i], mxr[i+1]);
	/* find best max_left + max_right */
	uint16_t mx = 0;
	int mxi = 0;
	for (int i=1; i<=s1.length(); i++) {
		if (mx < mxl[i]+mxr[i+1]) {
			mxi = i;
			mx = mxl[i]+mxr[i+1];
		}
	}
	/* map it back to subtrings */
	string a;
	for (int i=1; i<=s1.length(); i++) {
		if (mxl[mxi] == mxl[i]) {
			a = s1.substr(i-mxl[i], mxl[i]);
			break;
		}
	}
	string b;
	for (int i=s1.length(); i>=1; i--) {
		if (mxr[mxi+1] == mxr[i+1]) {
			b = s1.substr(i, mxr[i+1]);
			break;
		}
	}
	//cerr << mx << endl; // debug
	cout << a << endl;
	cout << b << endl;
	return 0;
}
