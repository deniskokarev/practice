void fw_inc(vector<int> &fw, int p, int inc) {
	int sz = fw.size();
	while (p<sz) {
		fw[p] += inc;
		p |= p+1;
	}
}

int fw_sum(vector<int> &fw, int p) {
	int sm = 0;
	while (p>=0) {
		sm += fw[p];
		p &= p+1;
		p--;
	}
	return sm;
}

class Solution {
	enum {END, START};
	struct EV {
		int id;
		int type;
		int t;
		bool operator<(const EV &o) const {
			return t<o.t || (t==o.t && type<o.type);
		}
	};
	static int find_free_server(vector<int> &fw, int first, int last) {
		int f=first, t=last;
		while (f<=t) {
			int mid = f+(t-f)/2;
			int sm = fw_sum(fw, mid) - fw_sum(fw, first-1);
			if (!sm)
				f = mid+1;
			else
				t = mid-1;
		}
		int fnd = t+1;
		if (fnd <= last && fw_sum(fw, fnd) - fw_sum(fw, fnd-1))
			return fnd;
		else
			return -1;
	}
public:
	static vector<int> busiestServers(int k, const vector<int>& arrival, const vector<int>& load) {
		int sz = arrival.size();
		vector<EV> ev(2*sz);
		for (int i=0; i<sz; i++)
			ev[i] = EV {i, START, arrival[i]};
		for (int i=0; i<sz; i++)
			ev[sz+i] = EV {i, END, arrival[i]+load[i]};
		sort(ev.begin(), ev.end());
		vector<int> fw(k);
		for (int s=0; s<k; s++)
			fw_inc(fw, s, +1);  // mark all servers free
		vector<int> evid2s(sz, -1);
		vector<int> stat(k);
		for (auto &e:ev) {
			if (e.type == END) {
				int s = evid2s[e.id];
				if (s >= 0)
					fw_inc(fw, s, +1); // +1 means make it free
			} else {
				int s_want = e.id % k;
				int fnd = find_free_server(fw, s_want, k-1);
				if (fnd < 0)
					fnd = find_free_server(fw, 0, s_want-1);
				if (fnd >= 0) {
					stat[fnd]++;
					evid2s[e.id] = fnd;
					fw_inc(fw, fnd, -1); // -1 make it busy
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

