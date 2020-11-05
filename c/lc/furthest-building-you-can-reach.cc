class Solution {
	static bool may_reach(const vector<int>& hdelta, int len, int bricks, int ladders) {
		if (len <= ladders) {
			return true;
		} else {
			vector<int> srt(hdelta.begin(), hdelta.begin()+len);
			sort(srt.begin(), srt.end());
			for (int i=0; i<len-ladders; i++)
				bricks -= srt[i];
			return bricks >= 0;
		}
	}
public:
	static int furthestBuilding(const vector<int>& heights, int bricks, int ladders) {
		int sz = heights.size();
		vector<int> hdelta(sz);
		hdelta[0] = 0;
		for (int i=1; i<sz; i++)
			hdelta[i] = max(0, heights[i] - heights[i-1]);
		int f=1, t=sz;
		while (f<=t) {
			int m = (f+t)/2;
			if (may_reach(hdelta, m, bricks, ladders))
				f = m+1;
			else
				t = m-1;
		}
		return f-2;
	}
};

