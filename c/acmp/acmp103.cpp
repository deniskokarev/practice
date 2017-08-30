/* ACMP 103 problem */

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	string a, b;
	cin >> a >> b;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	while (a.length() < 100)
		a.push_back('0');
	while (b.length() < 100)
		b.push_back('0');
	string res;
	int carry = 0;
	for (int i=0; i<a.length(); i++) {
		int d = carry+a[i]+b[i]-'0'-'0';
		carry = d/10;
		res.push_back(d%10+'0');
	}
	res.push_back(carry+'0');
	//cerr << a << '\n' << b << '\n' << res << '\n';
	int e;
	for (e=res.length()-1; e>=0 && res[e]=='0'; e--);
	res = res.substr(0,e+1);
	reverse(res.begin(), res.end());
	if (res.length() == 0)
		res = "0";
	cout << res << endl;
	return 0;
}
