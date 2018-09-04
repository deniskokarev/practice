#include <iostream>
#include <vector>
/* CodeForces CF988E problem */
using namespace std;

bool mv2r(string &s, char ch, int pos, int &cnt) {
	bool fnd = false;
	for (int i=pos; i>=0; i--) {
		if (s[i] == ch) {
			for (int j=i; j<pos; j++) {
				swap(s[j], s[j+1]);
				cnt++;
			}
			fnd = true;
			break;
		}
	}
	return fnd;
}

bool mvz(string &s, int &cnt) {
	if (s[0] != '0') {
		return true;
	} else if (s.size() > 2) {
		int i;
		for (i=1; i<s.size()-2 && s[i] == '0'; i++);
		if (s[i] != '0' && i < s.size()-2) {
			for (int j=i; j>0; j--) {
				swap(s[j-1], s[j]);
				cnt++;
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	if (s.size() < 2) {
		cout << -1 << endl;
		return 0;
	}
	// try last 00, 25, 50 and 75
	int acnt00 = INT_MAX, acnt25 = INT_MAX, acnt50 = INT_MAX, acnt75 = INT_MAX;
	int c00 = 0, c25 = 0;
	int c50, c75;
	string s00 = s, s25 = s;
	string s50, s75;
	if (mv2r(s00, '0', s00.size()-1, c00)) {
		s50 = s00;
		c50 = c00;
		if (mv2r(s00, '0', s00.size()-2, c00))
			if (mvz(s00, c00))
				acnt00 = c00;
		if (mv2r(s50, '5', s50.size()-2, c50))
			if (mvz(s50, c50))
				acnt50 = c50;
	}
	if (mv2r(s25, '5', s25.size()-1, c25)) {
		s75 = s25;
		c75 = c25;
		if (mv2r(s25, '2', s25.size()-2, c25))
			if (mvz(s25, c25))
				acnt25 = c25;
		if (mv2r(s75, '7', s75.size()-2, c75))
			if (mvz(s75, c75))
				acnt75 = c75;
	}
#if 0
	cerr << s00 << ' ' << acnt00 << endl;
	cerr << s25 << ' ' << acnt25 << endl;
	cerr << s50 << ' ' << acnt50 << endl;
	cerr << s75 << ' ' << acnt75 << endl;
#endif
	if (acnt00 < INT_MAX || acnt25 < INT_MAX || acnt50 < INT_MAX || acnt75 < INT_MAX) {
		cout << min(acnt00, min(acnt25, min(acnt50, acnt75))) << endl;
	} else {
		cout << -1 << endl;
	}
	return 0;
}
