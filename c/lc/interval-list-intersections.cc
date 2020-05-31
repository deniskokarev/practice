// https://leetcode.com/problems/interval-list-intersections/
class Solution {
public:
	static vector<vector<int>> intervalIntersection(const vector<vector<int>>& aa, const vector<vector<int>>& bb) {
		vector<pair<int,int>> vv1(2*aa.size());
		for (int i=0; i<aa.size(); i++) {
			vv1[2*i] = {aa[i][0],-1};
			vv1[2*i+1] = {aa[i][1],+1};
		}
		vector<pair<int,int>> vv2(2*bb.size());
		for (int i=0; i<bb.size(); i++) {
			vv2[2*i] = {bb[i][0],-1};
			vv2[2*i+1] = {bb[i][1],+1};
		}
		vector<pair<int,int>> vv(vv1.size()+vv2.size());
		merge(vv1.begin(), vv1.end(), vv2.begin(), vv2.end(), vv.begin());
		vector<vector<int>> res;
		int h = 0;
		int b = -1;
		for (auto &v:vv) {
			int h_new = h - v.second;
			if (h_new == 2) {
				b = v.first;
			} else if (b >= 0) {
				res.push_back({b,v.first});
				b = -1;
			}
			h = h_new;
		}
		return res;
	}
};

