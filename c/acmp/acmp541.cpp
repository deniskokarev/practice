/* ACMP 541 problem */
#include <iostream>
#include <algorithm>
using namespace std;

// compare two ring buffers of same length
bool lessRing(const string &a, const string &b, int posA, int posB, int sz) {
	for (int i=0,ai=posA,bi=posB; i<sz; i++,ai++,bi++)
		if (a[ai%sz]<b[bi%sz])
			return true;
		else if (a[ai%sz]>b[bi%sz])
			return false;
	return false;
}

// compare strings as numbers
bool snLess(const string &a, const string &b) {
	return a.length()<b.length() || ((a.length()==b.length()) && (a<b));
}

// subtract strings as numbers where a>=b
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
	// find min b
	int minbi;
	for (minbi=0; minbi<b.length() && b[minbi]=='0'; minbi++);
	for (int i=minbi+1; i<b.length(); i++)
		if (b[i] != '0' && lessRing(b, b, i, minbi, b.length()))
			minbi = i;
	string minb(b.begin()+minbi, b.end());
	minb.append(b.begin(), b.begin()+minbi);
	// find max a
	int maxai;
	for (maxai=0; maxai<a.length() && a[maxai]=='0'; maxai++);
	for (int i=maxai+1; i<a.length(); i++)
		if (a[i] != '0' && lessRing(a, a, maxai, i, a.length()))
			maxai = i;
	string maxa(a.begin()+maxai, a.end());
	maxa.append(a.begin(), a.begin()+maxai);
	// subtract
	if (snLess(maxa, minb))
		cout << '-' << sub(minb, maxa) << endl;
	else
		cout << sub(maxa, minb) << endl;
	return 0;
}
