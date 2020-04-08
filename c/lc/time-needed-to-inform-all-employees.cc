class Solution {
    using G = vector<vector<int>>;
    int dfs_mx_time(const G &gg, const vector<int>& time, int root) {
        int mxt = 0;
        for (int c:gg[root])
            mxt = max(mxt, dfs_mx_time(gg, time, c));
        return mxt + time[root];
    }
public:
    int numOfMinutes(int sz, int root, vector<int>& tree, vector<int>& time) {
        G gg(sz);
        for (int i=0; i<tree.size(); i++) {
            int p = tree[i];
            int c = i;
            if (p >= 0)
                gg[p].push_back(i);
        }
        return dfs_mx_time(gg, time, root);
    }
};
