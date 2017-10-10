/* ACMP 994 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1 >> s2;
	/* matrix a-la max substring */
	vector<vector<uint16_t>> ssl(s1.length()+2, vector<uint16_t>(s2.length()+2, 0));
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			if (s1[i-1] == s2[j-1])
				ssl[i][j] = ssl[i-1][j-1]+1;
	vector<vector<uint16_t>> ssr(s1.length()+2, vector<uint16_t>(s2.length()+2, 0));
	for (int i=s1.length(); i>=1; i--)
		for (int j=s2.length(); j>=1; j--)
			if (s1[i-1] == s2[j-1])
				ssr[i][j] = ssr[i+1][j+1]+1;
	int mx = 0;
	int a = 0, al = 0;
	int b = 0, bl = 0;
	/* max from left */
	vector<uint16_t> mxl(s2.length()+2, 0);
	/* max from right */
	vector<uint16_t> mxr(s2.length()+2, 0);
	for (int i=1; i<=s1.length(); i++) {
		for (int j=1; j<=s2.length(); j++)
			mxl[j] = max(mxl[j], max(ssl[i][j], mxl[j-1]));
		for (int j=s2.length(); j>=1; j--)
			mxr[j] = max(mxr[j], max(ssr[i][j], mxr[j+1]));
		for (int j=1; j<=s2.length(); j++) {
			if (mx < mxl[j]+mxr[j+1]) {
				mx = mxl[j]+mxr[j+1];
				a = j-mxl[j];
				al = mxl[j];
				bl = mxr[j+1];
			}
		}
		for (int j=s2.length(); j>=1; j--) {
			if (bl == mxr[j]) {
				b = j-1;
				break;
			}
		}
	}
	cerr << mx << endl; // debug
	cout << s2.substr(a, al) << endl;
	cout << s2.substr(b, bl) << endl;
	return 0;
}
