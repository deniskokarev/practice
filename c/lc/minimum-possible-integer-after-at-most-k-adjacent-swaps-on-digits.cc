class Solution {
	static void fw_inc(vector<int> &fw, int p, int inc) {
		int sz = fw.size();
		for (int i=p; i<sz; i|=i+1)
			fw[i] += inc;
	}

	static int fw_sum(const vector<int> &fw, int p) {
		int sum = 0;
		for (int i=p; i>=0; i=(i&(i+1))-1)
			sum += fw[i];
		return sum;
	}
public:
	static string minInteger(const string &num, int k) {
		int sz = num.size();
		string in(num);
		vector<vector<int>> pos(10);
		for (int d=0; d<10; d++) {
			for (int p=0; p<sz; p++)
				if (num[p] == '0'+d)
					pos[d].push_back(p);
			reverse(pos[d].begin(), pos[d].end());
		}
		string res;
		vector<int> fw(sz);
		while (k && res.size() < sz) {
			for (int d=0; d<10; d++) {
				if (!pos[d].empty()) {
					int pd = pos[d].back();
					int dist = pd - fw_sum(fw, pd);
					if (dist <= k) {
						pos[d].pop_back();
						res.push_back('0' + d);
						fw_inc(fw, pd, +1);
						k -= dist;
						in[pd] = ' ';
						break;
					}
				}
			}
		}
		for (auto c:in)
			if (c != ' ')
				res.push_back(c);
		return res;
	}
};
