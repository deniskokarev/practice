bool dfs_place(vector<int> &res, int pos, int n, bitset<21> &taken) {
	int sz = res.size();
	if (pos == sz)
		return taken.all();
	if (res[pos] != 1)
		return dfs_place(res, pos+1, n, taken);
	for (int i=20; i>1; i--) {
		if (!taken[i] && pos+i < sz && res[pos+i] == 1) {
			taken[i] = 1;
			res[pos] = res[pos+i] = i;
			if (dfs_place(res, pos+1, n, taken))
				return true;
			taken[i] = 0;
			res[pos] = res[pos+i] = 1;
		}
	}
	// try to keep 1
	if (dfs_place(res, pos+1, n, taken))
		return true;
	else
		return false;
}

class Solution {
public:
	static vector<int> constructDistancedSequence(int n) {
		vector<int> res(n*2-1, 1);
		bitset<21> taken;
		for (int i=0; i<21; i++)
			taken[i] = 1;
		for (int i=2; i<=n; i++)
			taken[i] = 0;
		dfs_place(res, 0, n, taken);
		return res;
	}
};
