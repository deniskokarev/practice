class Solution {
public:
	static int numRescueBoats(const vector<int>& people, int limit) {
		vector<int> pp(people);
		sort(pp.begin(), pp.end());
		int sz = pp.size();
		int cnt = 0;
		int i = 0, j = sz-1;
		while (i < j) {
			if (pp[j] + pp[i] <= limit)
				j--, i++, cnt++;
			else
				j--, cnt++;
		}
		cnt += (i==j);
		return cnt;
	}
};
