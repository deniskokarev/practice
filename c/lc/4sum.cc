// CPU: O(n*n*log(n) + result_size), theoretically faster than author's O(n^3)
// Mem: O(n*n*log(n))


// We store (a,b) pairs in 2D structure. 1st dimension is Fenwick tree keyed by pos b
// 2nd dimension is hashmap keyed by a+b, which stores (a,b) pairs
// During retrieval, for every (c,d) walking from the right find the corresponding (a,b)
// that lies to the left of c and having key = target - (c+d)
class Solution {
	using M2L = unordered_map<int, vector<pair<int,int>>>;
	using FW = vector<M2L>;
public:
	void fw_register(FW &fw, int a, int b, int b_pos) {
		int sz = fw.size();
		auto k = a + b;
		auto p = b_pos;
		auto ab = make_pair(a, b);
		while (p < sz) {
			fw[p][k].push_back(ab);
			p |= (p+1);
		}
	}
	void fw_retrieve(vector<vector<int>> &res, const FW &fw, int c, int d, int c_pos, int tgt) {
		auto k = tgt - (c + d);
		auto p = c_pos-1;
		while (p >= 0) {
			auto fnd_abs = fw[p].find(k);
			if (fnd_abs != fw[p].end())
				for (auto &ab: fnd_abs->second)
					res.push_back({ab.first, ab.second, c, d});
			p = (p & (p+1)) - 1;
		}
	}
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int sz = nums.size();
		FW fw(sz, M2L(32));
		int lst_a = INT_MIN;
		for (int i=0; i<sz; i++) {
			auto a = nums[i];
			if (a == lst_a)
				continue;
			lst_a = a;
			int lst_b = INT_MAX;
			for (int j=i+1; j<sz; j++) {
				auto b = nums[j];
				if (b == lst_b)
					continue;
				lst_b = b;
				fw_register(fw, a, b, j);
			}
		}
		int lst_d = INT_MAX;
		vector<vector<int>> res;
		for (int j=sz-1; j>0; j--) {
			auto d = nums[j];
			if (d == lst_d)
				continue;
			lst_d = d;
			int lst_c = INT_MIN;
			for (int i=j-1; i>=0; i--) {
				auto c = nums[i];
				if (c == lst_c)
					continue;
				lst_c = c;
				fw_retrieve(res, fw, c, d, i, target);
			}
		}
		return res;
	}
};

