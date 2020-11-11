class Solution {
public:
	static string findLexSmallestString(const string &s, int a, int b) {
		int sz = s.size();
		int ofs = gcd(sz, b);
		int inc = gcd(a, 10);
		string mn(s);
		if (ofs&1) {
			for (int d0=0; d0<10; d0+=inc) {
				for (int d1=0; d1<10; d1+=inc) {
					string str(s);
					for (int i=0; i<sz; i+=2)
						str[i] = (((str[i]-'0') + d0) % 10)+'0';
					for (int i=1; i<sz; i+=2)
						str[i] = (((str[i]-'0') + d1) % 10)+'0';
					for (int pos=0; pos<sz; pos+=ofs) {
						string cmp((str+str).substr(pos, sz));
						mn = min(mn, cmp);
					}
				}
			}
		} else {
			for (int d=0; d<10; d+=inc) {
				string str(s);
				for (int i=1; i<sz; i+=2)
					str[i] = (((str[i]-'0') + d) % 10)+'0';
				for (int pos=0; pos<sz; pos+=ofs) {
					string cmp((str+str).substr(pos, sz));
					mn = min(mn, cmp);
				}
			}
		}
		return mn;
	}
};

