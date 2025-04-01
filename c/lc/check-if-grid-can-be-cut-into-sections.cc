// https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections
// compute non-overlapping intervals in batch mode
class Solution {
	struct Iv {
		int b, e;
		bool operator<(const Iv &rhs) const { return b < rhs.b; }
	};

	static bool may_cut_3(vector<Iv> &srt) {
		sort(srt.begin(), srt.end());
		vector<Iv> ivs;
		ivs.push_back({-1, -1});
		for (auto iv: srt) {
			const auto &back = ivs.back();
			if (back.e > iv.b) {
				iv.b = back.b;
				iv.e = max(iv.e, back.e);
				ivs.pop_back();
			}
			ivs.push_back(iv);
		}
#if 0
		for (auto iv: ivs) {
			cerr << iv.b << " " << iv.e << "\n";
		}
#endif
		return ivs.size() > 3;
	}

public:
	static bool checkValidCuts(int unused, const vector<vector<int>> &rectangles) {
		int sz = rectangles.size();
		vector<Iv> srt(sz);
		// x
		int i = 0;
		for (const auto &r: rectangles) { srt[i++] = {r[0], r[2]}; }
		if (may_cut_3(srt)) { return true; }
		// y
		i = 0;
		for (const auto &r: rectangles) { srt[i++] = {r[1], r[3]}; }
		return may_cut_3(srt);
	}
};

