class Solution {
public:
	static string maximumBinaryString(const string &b) {
		int sz = b.size();
		string out(sz, '0');
		int i = 0;
		while (i < sz && b[i] == '1')
			out[i++] = '1';
		int j = i+1;
		while (j < sz) {
			while (j < sz && b[j] == '1')
				j++;
			if (j < sz)
				out[i++] = '1';
			j++;
		}
		i++;
		while (i < sz)
			out[i++] = '1';
		return out;
	}
};
