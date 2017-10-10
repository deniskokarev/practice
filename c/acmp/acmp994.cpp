/* ACMP 994 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	string sa, sb;
	cin >> sa >> sb;
	string &s1 = (sa.length() < sb.length()) ? sa : sb;
	string &s2 = (sa.length() >= sb.length()) ? sa : sb;
	/* matrix a-la max substring */
	vector<vector<uint16_t>> ss(s1.length()+2, vector<uint16_t>(s2.length()+2, 0));
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			if (s1[i-1] == s2[j-1])
				ss[i][j] = ss[i-1][j-1]+1;
	for (int i=s1.length(); i>=0; i--)
		for (int j=s2.length(); j>=1; j--)
			if (ss[i][j] != 0)
				ss[i][j] = max(ss[i][j], ss[i+1][j+1]);
	int mx = 0;
	int ai = 0, al = 0;
	int bi = 0, bl = 0;
	for (int j=1; j<=s2.length(); j++) {
		/* max from left */
		vector<uint16_t> mxl(s1.length()+2, 0);
		for (int i=1; i<=s1.length(); i++)
			mxl[i] = max(ss[i][j], mxl[i-1]);
		/* max from right */
		vector<uint16_t> mxr(s1.length()+2, 0);
		for (int i=s1.length(); i>=1; i--)
			mxr[i] = max(ss[i][j], mxr[i+1]);
		for (int i=1; i<s1.length(); i++) {
			if (mx < mxl[i]+mxr[i+1]) {
				mx = mxl[i]+mxr[i+1];
				ai = i-1;
				al = mxl[i];
			}
		}
		for (int i=s1.length(); i>ai+mx; i--) {
			if (mxr[ai+1] == mxr[i]) {
				bi = i-mxr[i];
				bl = mxr[i];
				break;
			}
		}
	}
	//cerr << mx << endl; // debug
	cout << s1.substr(ai, al) << endl;
	cout << s1.substr(bi, bl) << endl;
	return 0;
}
