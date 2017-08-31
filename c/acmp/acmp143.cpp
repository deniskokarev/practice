/* ACMP 143 problem */

#include <iostream>
#include <algorithm>

using namespace std;

#define dim(X) (sizeof(X)/sizeof(X[0]))

bool myless(const string &a, const string &b) {
	return a.length()<b.length() ||
					  (a.length()==b.length() && a<b);
}

string sub(const string &a, const string &b) {
	string ra(a), rb(b);
	reverse(ra.begin(), ra.end());
	reverse(rb.begin(), rb.end());
	while (rb.length() < ra.length())
		rb.push_back('0');
	string res;
	int carry = 0;
	for (int i=0; i<a.length(); i++) {
		int da = ra[i]-'0';
		int db = rb[i]-'0';
		res.push_back((da+carry+10-db)%10+'0');
		carry = (da+carry < db)?-1:0;
	}
	int e;
	for (e=res.length()-1; e>0 && res[e]=='0'; e--);
	res.resize(e+1);
	reverse(res.begin(), res.end());
	return res;
}

int main(int argc, char **argv) {
	string a, b;
	cin >> a >> b;
	string minus;
	if (myless(a,b)) {
		swap(a, b);
		minus = "-";
	}
	cout << minus << sub(a, b) << endl;
	return 0;
}
