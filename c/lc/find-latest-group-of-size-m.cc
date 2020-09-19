class Solution {
public:
	static int findLatestStep(const vector<int>& arr, int m) {
		int sz = arr.size();
		map<int,int> seg;
		seg[-2] = 0;
		seg[sz+2] = 0;
		vector<int> cnt(sz+1);
		int mx = -2;
		for (int i=0; i<sz; i++) {
			auto ins = seg.insert({arr[i], 1});
			auto it = ins.first;
			auto nxt = next(it);
			auto prv = prev(it);
			cnt[1]++;
			if (nxt->first == arr[i]+1) {
				cnt[nxt->second]--;
				cnt[it->second]--;
				it->second += nxt->second;
				cnt[it->second]++;
				seg.erase(nxt);
			}
			if (prv->first+prv->second == arr[i]) {
				cnt[prv->second]--;
				cnt[it->second]--;
				prv->second += it->second;
				cnt[prv->second]++;
				seg.erase(it);
			}
			if (cnt[m])
				mx = max(mx, i);
		}
		return mx+1;
	}
};

