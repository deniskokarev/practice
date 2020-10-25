// https://leetcode.com/contest/weekly-contest-212/problems/path-with-minimum-effort/
class Solution {
	struct Q {
		int cost;
		int x, y;
		int mx_cost;
		bool operator>(const Q &o) const {
			return cost > o.cost;		  
		}
	};
	struct P {
		int x,y;
	};
public:
	static int minimumEffortPath(const vector<vector<int>>& heights) {
		int h = heights.size();
		int w = heights[0].size();
		vector<vector<int>> cost(h, vector<int>(w, INT_MIN));
		priority_queue<Q, vector<Q>, greater<Q>> qq;
		qq.push(Q{0,0,0,0});
		while (!qq.empty()) {
			auto p = qq.top();
			cost[p.y][p.x] = max(p.cost, p.mx_cost);
			qq.pop();
			if (p.y == h-1 && p.x == w-1)
				break;
			for (P mv:(P[]){{-1,0}, {0,-1}, {1,0}, {0,1}}) {
				int x = p.x + mv.x;
				int y = p.y + mv.y;
				if (x>=0 && x<w && y>=0 && y<h && cost[y][x]==INT_MIN) {
					int cost = abs(heights[y][x]-heights[p.y][p.x]);
					qq.push(Q{cost, x, y, max(cost, p.mx_cost)});
				}
			}
		}
		return cost[h-1][w-1];
	}
};

