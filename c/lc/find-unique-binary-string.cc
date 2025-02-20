// https://leetcode.com/problems/find-unique-binary-string
class Solution {
public:
	static string findDifferentBinaryString(const vector<string> &nn) {
		int bsz = nn[0].size();
		// full tree nodes with children count, root=1
		vector<int> ncnt(2 * (1 << bsz));
		for (auto &n: nn) {
			int r = 1;
			ncnt[r]++;
			for (const char cb: n) {
				r *= 2;
				r += cb - '0';
				ncnt[r]++;
			}
		}
		string ans(bsz, '0');
		for (int rt = 1, lvl = 0; lvl < bsz; ++lvl) {
			const int l = 2 * rt;
			const int r = 2 * rt + 1;
			const int b = (ncnt[l] > ncnt[r]);
			ans[lvl] += b;
			rt = 2 * rt + b;
		}
		return ans;
	}
};

class Solution {
public:
    string findDifferentBinaryString(const vector<string>& ss) {
        int sz = ss[0].size();
        int mxsz = 1<<sz;
        int msk = mxsz-1;
        vector<bool> hh(mxsz, false);
        for (auto &s:ss) {
             auto n = ::strtol(s.c_str(), nullptr, 2) & msk;
             hh[n] = true;
        }
        for (int i=0; i<mxsz; i++) {
            if (!hh[i]) {
                constexpr int MXSZ = 16;
                std::bitset<MXSZ> b(i);
                return b.to_string().substr(MXSZ - sz);
            }
        }
        return "oops";
    }
};
