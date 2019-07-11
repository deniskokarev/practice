#include <iostream>
#include <vector>
/* CodeForces CF1153C problem */
using namespace std;

int code(char ch) {
	if (ch == '(')
		return +1;
	else if (ch == ')')
		return -1;
	else
		return 0;
}

bool greedy(const string &s, string &res) {
	vector<int> rr(s.size()+1);
	for (int i=s.size()-1; i>=0; i--)
		rr[i] = code(s[i]) + rr[i+1];
	int lcnt = 0;
	for (int i=0; i<s.size(); i++) {
		if (s[i] == '?') {
			if (lcnt + rr[i+1] > 0) {
				res[i] = ')';
				lcnt--;
			} else {
				res[i] = '(';
				lcnt++;
			}
		} else {
			lcnt += code(s[i]);
		}
		if (lcnt < 0)
			return false;
	}
	return (lcnt == 0);
}

int main(int argc, char **argv) {
	int n;
	string s;
	cin >> n;
	cin >> s;
	int l=0, r=n-1;
	if (s.size() % 2 == 0) {
		if (
			(s[l] == '?' && s[r] == '?') ||
			(s[l] == '(' && s[r] == '?') ||
			(s[l] == '?' && s[r] == ')') ||
			(s[l] == '(' && s[r] == ')')
		) {
			s[l] = '(';
			s[r] = ')';
			string res(s);
			if (greedy(s, res)) {
				cout << res << endl;
				return 0;
			}
		}
	}
	cout << ":(" << endl;
	return 0;
}
