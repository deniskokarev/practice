/* ACMP 252 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cassert>

using namespace std;

pair<int,string> num2sn(unsigned n) {
	char s[32];
	int sz = 0;
	do {
		s[sz++] = '0'+(n%10);
		n /= 10;
	} while (n>0);
	int i = 0;
	int p = 0;
	for (i=0; s[i]=='0' && i<sz-1; i++,p++);
	string sm = "";
	for (int j=sz-1; j>=i; j--,p++)
		sm += s[j];
	return make_pair(p,sm);
}

int main() {
	int n;
	cin >> n;
	vector<tuple<int, string, int, int, string>> mm(n);
	int i = 0;
	for (auto &m:mm) {
		int d;
		string su;
		cin >> d >> su;
		unsigned mantissa = 1;
		int pow10 = 1;
		switch(su[su.size()-1]) {
		case 'g':
			mantissa = 1;
			pow10 = 3;
			break;
		case 'p':
			mantissa = 16380;
			pow10 = 3;
			break;
		case 't':
			mantissa = 1;
			pow10 = 9;
			break;
		default:
			assert(false && "unexpected gpt value");
		}
		if (su.size()>1) {
			switch(su[0]) {
			case 'm':
				pow10 -= 3;
				break;
			case 'k':
				pow10 += 3;
				break;
			case 'M':
				pow10 += 6;
				break;
			case 'G':
				pow10 += 9;
				break;
			default:
				assert(false && "unexpected mkMG value");
			}
		}
		if (su == "mt") {
			// exceptional case, mt == kg
			mantissa = 1;
			pow10 = 6;
		}
		auto sn = num2sn(mantissa*d);
		m = make_tuple(sn.first+pow10, sn.second, i++, d, su);
		if (get<1>(m) == "0")
			get<0>(m) = 0;
	}
	sort(mm.begin(), mm.end());
	for (auto &m:mm)
		cout << get<3>(m) << ' ' << get<4>(m) << endl;
	//		cout << get<0>(m) << ' ' << get<1>(m) << " = " << get<3>(m) << ' ' << get<4>(m) << endl;
	return 0;
}

