class Solution {
public:
	static int eatenApples(const vector<int>& apples, const vector<int>& days) {
		constexpr int MXD = 4e4+1;
		int sz = apples.size();
		vector<int> app(MXD);
		priority_queue<pair<int,int>,vector<pair<int,int>>,std::greater<pair<int,int>>> rot; // (when,what_app_bucket)
		int sm = 0;
		int ans = 0;
		for (int d=0; d<MXD; d++) {
			if (d < sz && apples[d] > 0) {
				app[d] = apples[d];
				sm += app[d];
				rot.push({d+days[d], d});
			}
			while (!rot.empty()) {
				auto top = rot.top();
				if (top.first <= d || app[top.second] == 0) {
					sm -= app[top.second];
					rot.pop();
				} else {
					ans += (sm>0);
					sm--;
					app[top.second]--;
					break;
				}
			}
		}
		return ans;
	}
};
