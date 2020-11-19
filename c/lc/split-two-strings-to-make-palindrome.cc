class Solution {
public:
	static bool checkPalindromeFormation(const string &a, const string &b) {
		int sz = a.size();
		int p1sz, p2sz;
		int l, r;
		if (sz&1) {
			int m = sz/2;
			l = m-1;
			r = m+1;
			p1sz = p2sz = 1;
		} else {
			r = sz/2;
			l = r-1;
			p1sz = p2sz = 0;
		}
		for (int l1=l,r1=r; l1>=0 && a[l1] == a[r1]; l1--,r1++)
			p1sz += 2;
		for (int l2=l,r2=r; l2>=0 && b[l2] == b[r2]; l2--,r2++)
			p2sz += 2;
		bool res = false;
		string ar(a);
		reverse(ar.begin(), ar.end());
		string br(b);
		reverse(br.begin(), br.end());
		res |= a.substr(0,(sz-p1sz)/2) == br.substr(0,(sz-p1sz)/2);
		res |= a.substr(0,(sz-p2sz)/2) == br.substr(0,(sz-p2sz)/2);
		res |= b.substr(0,(sz-p1sz)/2) == ar.substr(0,(sz-p1sz)/2);
		res |= b.substr(0,(sz-p2sz)/2) == ar.substr(0,(sz-p2sz)/2);
		return res;
	}
};

