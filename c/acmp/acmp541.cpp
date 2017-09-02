/* ACMP 541 problem */

#include <iostream>
#include <algorithm>

using namespace std;

#define dim(X) (sizeof(X)/sizeof(X[0]))

bool lessCirc(const char *a, const char *b, int posA, int posB, int sz) {
	for (int i=0,ai=posA,bi=posB; i<sz; i++,ai++,bi++)
		if (a[ai%sz]<b[bi%sz])
			return true;
		else if (a[ai%sz]>b[bi%sz])
			return false;
	return false;
}

bool snLess(const string &a, const string &b) {
	return a.length()<b.length() || ((a.length()==b.length()) && (a<b));
}

// unsigned strings subtract where a>=b
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
	int minbi;
	for (minbi=0; minbi<b.length() && b[minbi]=='0'; minbi++);
	for (int i=minbi+1; i<b.length(); i++)
		if (b[i] != '0' && lessCirc(b.c_str(), b.c_str(), i, minbi, b.length()))
			minbi = i;
	string minb(b.c_str()+minbi, b.length()-minbi);
	minb.append(b.c_str(), minbi);
	int maxai;
	for (maxai=0; maxai<a.length() && a[maxai]=='0'; maxai++);
	for (int i=maxai+1; i<a.length(); i++)
		if (a[i] != '0' && lessCirc(a.c_str(), a.c_str(), maxai, i, a.length()))
			maxai = i;
	string maxa(a.c_str()+maxai, a.length()-maxai);
	maxa.append(a.c_str(), maxai);
	cerr << maxa << ' ' << minb << endl;
	if (snLess(maxa, minb))
		cout << '-' << sub(minb, maxa) << endl;
	else
		cout << sub(maxa, minb) << endl;
	return 0;
}
