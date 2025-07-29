// 



class Solution {
public:
	static vector<int> smallestSubarrays(const vector<int> &nn) {
		constexpr int B = 31;
		int sz = nn.size();
		// orr[i] = Disjunct(i..sz-1)
		vector<int> orr(nn);
		orr.push_back(0);
		// pos[bit,i] = min(p), such that (nums[p] | bit) != 0
		vector<vector<int>> pos(B, vector<int>(sz + 1, 0));
		for (int i = sz - 1; i >= 0; i--) {
			orr[i] |= orr[i + 1];
			for (int b = 0; b < B; b++) {
				int p = 1 << b;
				if (nn[i] & p)
					pos[b][i] = i;
				else
					pos[b][i] = pos[b][i + 1];
			}
		}
		vector<int> res(sz, 0);
		for (int i = 0; i < sz; i++) {
			int mx = i;
			for (int b = 0; b < B; b++) {
				int p = 1 << b;
				if (orr[i] & p)
					mx = max(mx, pos[b][i]);
			}
			res[i] = mx - i + 1;
		}
		return res;
	}
};

