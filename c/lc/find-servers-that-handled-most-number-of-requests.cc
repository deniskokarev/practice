class Solution {
	enum {EV_END, EV_START};
	struct EV {
		int id;
		int ev_type;
		int t;
		bool operator<(const EV &o) const {
			return t<o.t || (t==o.t && ev_type<o.ev_type);
		}
	};
public:
	static vector<int> busiestServers(int k, const vector<int>& arrival, const vector<int>& load) {
		int sz = arrival.size();
		vector<EV> ev(2*sz);
		for (int i=0; i<sz; i++)
			ev[i] = EV {i, EV_START, arrival[i]};
		for (int i=0; i<sz; i++)
			ev[sz+i] = EV {i, EV_END, arrival[i]+load[i]};
		sort(ev.begin(), ev.end());
		vector<int> evid2s(sz, -1);
		vector<int> stat(k);
		set<int> free;
		for (int s=0; s<k; s++)
			free.insert(s), free.insert(s+k);
		for (auto &e:ev) {
			if (e.ev_type == EV_END) {
				int s = evid2s[e.id];
				if (s >= 0)
					free.insert(s), free.insert(s+k);
			} else {
				int s_want = e.id % k;
				auto fnd = free.lower_bound(s_want);
				if (fnd != free.end()) {
					int s = *fnd % k;
					stat[s]++;
					evid2s[e.id] = s;
					free.erase(s);
					free.erase(s+k);
				}
			}
		}
		int mx = *max_element(stat.begin(), stat.end());
		vector<int> res;
		for (int s=0; s<k; s++)
			if (stat[s] == mx)
				res.push_back(s);
		return res;
	}
};

