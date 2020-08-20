class Solution {
	struct P {
		int x, y;
	};
public:
	static int findMaxValueOfEquation(const vector<vector<int>>& points, int k) {
		deque<P> qq;
		int mx = INT_MIN;
		for (auto &v:points) {
			P p {v[0],v[1]};
			while (!qq.empty() && (p.x - qq.front().x) > k)
				qq.pop_front();
			if (!qq.empty())
				mx = max(mx, p.x - qq.front().x + qq.front().y + p.y);
			while (!qq.empty() && (p.x-qq.back().x) + qq.back().y < p.y)
				qq.pop_back();
			qq.push_back(p);
		}
		return mx;
	}
};

