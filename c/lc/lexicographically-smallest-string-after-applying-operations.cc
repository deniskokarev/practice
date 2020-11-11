class Solution {
public:
	static string findLexSmallestString(const string &s, int a, int b) {
		string s2 = s+s;
		int sz = s.size();
		int ofs = gcd(sz, b);
		int d1_inc = gcd(a, 10);
		int d0_inc;
		if (ofs&1)
			d0_inc = d1_inc;
		else
			d0_inc = 10; // only 1 iteration
		string mn(s);
		string str(sz, ' ');
		for (int pos=0; pos<sz; pos+=ofs) {
			for (int d0=0; d0<10; d0+=d0_inc) {
				for (int d1=0; d1<10; d1+=d1_inc) {
					for (int i=0; i<sz; i+=2)
						str[i] = (((s2[i+pos]-'0') + d0) % 10)+'0';
					for (int i=1; i<sz; i+=2)
						str[i] = (((s2[i+pos]-'0') + d1) % 10)+'0';
					mn = min(mn, str);
				}
			}
		}
		return mn;
	}
};

