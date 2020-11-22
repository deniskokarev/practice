class Solution {
	static int parse_t(const string &st) {
		return stoi(st.substr(0,2))*60+stoi(st.substr(3,2)); 
	}
	struct E {
		int t;
		string nm;
		E(const string &st, const string &nm):t(parse_t(st)),nm(nm) {
		}
		bool operator<(const E &o) const {
			return t < o.t;
		}
	};
public:
	static vector<string> alertNames(const vector<string>& keyName, const vector<string>& keyTime) {
		int sz = keyName.size();
		vector<E> ee;
		for (int i=0; i<sz; i++)
			ee.push_back(E(keyTime[i], keyName[i]));
		sort(ee.begin(), ee.end());
		set<string> viol;
		map<string,list<int>> nmt;
		for (int r=0; r<sz; r++) {
			const string &nm = ee[r].nm;
			int t = ee[r].t;
			list<int> &tl = nmt[nm];
			while (!tl.empty() && t-tl.front() > 60)
				tl.pop_front();
			tl.push_back(t);
			if (tl.size() >= 3)
				viol.insert(nm);
		}
		return {viol.begin(), viol.end()};
	}
};
