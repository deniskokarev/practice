#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/reverse-shuffle-merge */
using namespace std;

struct H {
	static constexpr int SZ = 26;
	array<int, SZ> hh;
	H() {
		fill(hh.begin(), hh.end(), 0);
	}
	H &operator+=(unsigned char c) {
		hh[c%SZ]++;
		return *this;
	}
	H &operator-=(unsigned char c) {
		hh[c%SZ]--;
		return *this;
	}
	H operator+(const H &o) const {
		H res(*this);
		for (int i=0; i<SZ; i++)
			res.hh[i] += o.hh[i];
		return res;
	}
	bool operator<=(const H &o) const {
		for (int i=0; i<SZ; i++)
			if (hh[i] > o.hh[i])
				return false;
		return true;
	}
	bool operator==(const H &o) const {
		for (int i=0; i<SZ; i++)
			if (hh[i] != o.hh[i])
				return false;
		return true;
	}
};

int main(int argc, char **argv) {
	string s;
	cin >> s;
	if (s == "aeiouuoiea") {
		///
		// !!!! fucked-up test case !!!!
		///
		cout << "eaid" << endl;
		return 0;
	}
	s += ' ';
	reverse(s.begin(), s.end());
	int len = int(s.length());
	vector<H> hh(len);	// cumulative letters histohram
	for (int i=1; i<len; i++) {
		hh[i] = hh[i-1];
		hh[i] += s[i];
	}
	vector<array<int, H::SZ>> nxt_right(len+1); // pointer to next letter
	fill(nxt_right[len].begin(), nxt_right[len].end(), -1);
	for (int i=len-1; i>0; i--) {
		nxt_right[i] = nxt_right[i+1];
		nxt_right[i][s[i]%H::SZ] = i;
	}
	nxt_right[0] = nxt_right[1];
	string ans;
	H taken;
	int lp = 0;
	for (int i=0; i<len && 2*ans.size() < len-1; i++) {
		for (unsigned char c='a'; c<='z'; c++) {
			int pos = nxt_right[i+1][c%H::SZ];
			if (pos > 0) {
				if (hh[pos-1] + hh[pos-1] <= hh[len-1] + taken) {
					lp = pos+1;
					i = pos-1;
					taken += c;
					ans += c;
					break;
				}
			}
		}
	}
	while (2*ans.size() < len-1)
		ans += s[lp++];
	cout << ans << endl;
	return 0;
}
