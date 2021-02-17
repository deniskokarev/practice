class Solution {
public:
	vector<int> decode(const vector<int>& enc) {
		// XOR [p] = p1 ^ p2 ^ p3 ^ p4 ^ p5 = XOR 1..5
		// XOR       e1        e3
		// => p5 = XOR 1..5 XOR e1 e3
		int sz = enc.size();
		int e_odd = 0;
		for (int i=0; i<sz; i+=2)
			e_odd ^= enc[i];
		int x_all = 0;
		for (int i=1; i<=sz+1; i++)
			x_all ^= i;
		vector<int> p(sz+1);
		p[sz] = x_all ^ e_odd;
		for (int i=sz-1; i>=0; i--)
			p[i] = p[i+1] ^ enc[i];
		return p;
	}
};
