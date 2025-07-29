// https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or

// correct approach, but still filing some tests
class Solution {
	static constexpr int B = 32;

	struct MxTree {
		int mx[2 * B]{};

		int after_set(int p, int v) {
			mx[p + B] = v;
			for (int nd = p + B; nd > 0; nd /= 2) {
				int sib = (nd & 1) ? nd - 1 : nd + 1;
				mx[nd / 2] = max(mx[nd], mx[sib]);
			}
			return mx[1];
		}
	};

public:
	static vector<int> smallestSubarrays(const vector<int> &nn) {
		int sz = nn.size();
		MxTree mxt;
		vector<int> res(sz);
		int mx = sz - 1;
		for (int i = sz - 1; i >= 0; i--) {
			for (int b = 0; b < B; b++) {
				if ((1 << b) & nn[i]) {
					mx = mxt.after_set(b, i);
				}
			}
			res[i] = mx - i + 1;
		}
		return res;
	}
};

// working, but slower and memory hungry
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

