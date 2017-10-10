/* ACMP 994 */
#include <iostream>
#include <cassert>

using namespace std;

/* upper left -> bottom right */
uint16_t ssl[2002][2002];
/* bottom right -> upper left */
uint16_t ssr[2002][2002];
/* technically, ssl and ssr could be reused for mxl and mxr, but we're still going to be under 64MB */
/* max common substring from the upper left */
uint16_t mxl[2002][2002];
/* max common substring from the bottom right */
uint16_t mxr[2002][2002];

int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1 >> s2;
	assert(s1.length() < 2001 && s2.length() < 2001);
	/* filling matrixes a-la max substring in all directions */
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			if (s1[i-1] == s2[j-1])
				ssl[i][j] = ssl[i-1][j-1]+1;
	for (int i=s1.length(); i>=1; i--)
		for (int j=s2.length(); j>=1; j--)
			if (s1[i-1] == s2[j-1])
				ssr[i][j] = ssr[i+1][j+1]+1;
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			mxl[i][j] = max(ssl[i][j], max(mxl[i-1][j], mxl[i][j-1]));
	for (int i=s1.length(); i>=1; i--)
		for (int j=s2.length(); j>=1; j--)
			mxr[i][j] = max(ssr[i][j], max(mxr[i+1][j], mxr[i][j+1]));
	/* find max total of common substring from the left + from the right */
	int mx = 0;		// total len
	int mxi = 0;	// which row mx was found
	int a = 0, al = 0;
	int b = 0, bl = 0;
	for (int i=1; i<=s1.length(); i++) {
		for (int j=1; j<=s2.length(); j++) {
			if (mx < mxl[i][j]+mxr[i][j+1]) {
				mx = mxl[i][j]+mxr[i][j+1];
				mxi = i;
				a = j-mxl[i][j];
				al = mxl[i][j];
				bl = mxr[i][j+1];
			}
		}
	}
	for (int j=s2.length(); j>a; j--) {
		if (bl == mxr[mxi][j]) {
			b = j-1;
			break;
		}
	}
	//cerr << mx << endl; // debug
	cout << s2.substr(a, al) << endl;
	cout << s2.substr(b, bl) << endl;
	return 0;
}
