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

class Solution {
	static constexpr int MX = 1e5;
	static constexpr int MOD = 1e9+7;
public:
	static int createSortedArray(const vector<int>& instructions) {
		int sz = instructions.size();
		vector<int> fw(MX+1);
		int64_t sm = 0;
		for (int i=0; i<sz; i++) {
			int v = instructions[i];
			int cnt_lt = fw_sum(fw, v-1);
			int cnt_le = fw_sum(fw, v);
			int cnt_gt = i - cnt_le;
			sm += min(cnt_lt, cnt_gt);
			fw_inc(fw, v, 1);
		}
		return sm % MOD;
	}
};

