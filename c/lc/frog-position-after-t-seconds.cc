class Solution {
	using G = vector<vector<int>>;
public:
	static double frogPosition(int sz, const vector<vector<int>> &edges, int t, int target) {
		G gg(sz);
		vector<int> e_cnt(sz);
		for (auto &e:edges) {
			gg[e[0]-1].push_back(e[1]-1);
			gg[e[1]-1].push_back(e[0]-1);
			e_cnt[e[0]-1]++;
			e_cnt[e[1]-1]++;
		}
		vector<double> prob(sz, 0.0);
		vector<int> time(sz, 0);
		prob[0] = 1.0;
		e_cnt[0]++;
		queue<int> qq;
		qq.push(0);
		while (!qq.empty()) {
			int p = qq.front();
			qq.pop();
			for (int c:gg[p]) {
				if (prob[c] == 0.0) {
					if (e_cnt[p]>1)
						prob[c] = prob[p]/(e_cnt[p]-1);
					else
						prob[c] = prob[p];	// leaf
					time[c] = time[p]+1;
					qq.push(c);
				}
			}
		}
		target--;
		if (e_cnt[target] == 1)
			return (time[target] <= t) ? prob[target] : 0; // leaf
		else
			return (time[target] == t) ? prob[target] : 0;
	}
};

