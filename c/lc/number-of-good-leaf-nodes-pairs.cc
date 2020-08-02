class Solution {
    int dfs_cnt(const TreeNode* root, vector<int> &nlf, int dist) {
        int rc = 0;
        if (root) {
            if (root->left == nullptr && root->right == nullptr) {
                nlf[0] = 1;
            } else {
                vector<int> l_nlf(11), r_nlf(11);
                rc += dfs_cnt(root->left, l_nlf, dist);
                rc += dfs_cnt(root->right, r_nlf, dist);
                for (int i=0; i<=10; i++)
                    for (int j=0; j<=10; j++)
                        if (i+j+2 <= dist)
                            rc += l_nlf[i] * r_nlf[j];
                for (int i=0; i<10; i++)
                    nlf[i+1] = l_nlf[i] + r_nlf[i];
            }
        }
        return rc;
    }
public:
    int countPairs(const TreeNode* root, int dist) {
        vector<int> nlf(11);
        return dfs_cnt(root, nlf, dist);
    }
};
