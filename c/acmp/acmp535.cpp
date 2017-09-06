/* ACMP 535 problem */

#include <iostream>
#include <algorithm>

using namespace std;

string wr_add(const string &a, const string &b) {
	string ra(a), rb(b);
	reverse(ra.begin(), ra.end());
	reverse(rb.begin(), rb.end());
	int sz = max(ra.length(), rb.length());
	while(ra.length() < sz)
		ra.push_back('0');
	while(rb.length() < sz)
		rb.push_back('0');
	string res;
	for (int i=0; i<ra.length(); i++) {
		char o = (ra[i]+rb[i]-'0'-'0')%10+'0';
		char t = (ra[i]+rb[i]-'0'-'0')/10+'0';
		res.push_back(o);
		if (t != '0')
			res.push_back(t);
	}
	reverse(res.begin(), res.end());
	return res;
}

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	string a, b, c;
	cin >> a >> b >> c;
	string rr[] = {
		wr_add(a, wr_add(b, c)),
		wr_add(a, wr_add(c, b)),
		wr_add(c, wr_add(a, b)),
		wr_add(c, wr_add(b, a)),
		wr_add(b, wr_add(c, a)),
		wr_add(b, wr_add(a, c))
	};
	sort(rr, rr+dim(rr),
		 [](const string &a, const string &b){
			 return a.length()<b.length() ||
					(a.length()==b.length() && a<b);
		 });
	int sz = unique(rr, rr+dim(rr))-rr;
	if (sz == 1)
		cout << "NO" << endl;
	else
		cout << "YES" << endl;
	for (int i=0; i<sz; i++)
		cout << rr[i] << endl;
	return 0;
}
