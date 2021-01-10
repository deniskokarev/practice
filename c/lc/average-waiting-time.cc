class Solution {
	struct PT {
		int t;
		long w; 
	};
public:
	static double averageWaitingTime(const vector<vector<int>>& cust) {
		int sz = cust.size();
		vector<PT> pt(sz+1);
		double sm = 0;
		for (int i=0; i<sz; i++) {
			pt[i+1].t = cust[i][0];
			pt[i+1].w = max(0L, pt[i].w - cust[i][0] + pt[i].t) + cust[i][1];
			sm += pt[i+1].w;
		}
		return sm / sz;
	}
};

