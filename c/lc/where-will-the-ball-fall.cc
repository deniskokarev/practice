// faster https://leetcode.com/problems/where-will-the-ball-fall/
class Solution {
public:
    vector<int> findBall(const vector<vector<int>>& gg) {
        int h = gg.size();
        int w = gg[0].size();
        vector<int> ans(w);
        for (int i=0; i<w; i++)
            ans[i] = i;
        // iterating over balls is faster, as we can terminate early
        for (int b=0; b<w; b++) {
            for (int r=0; r<h; r++) {
                int c = ans[b];
                if (c >= 0) {
                    if (gg[r][c] == 1 && c+1 < w && gg[r][c+1] == 1) {
                        ans[b]++;
                    } else if (gg[r][c] == -1 && c-1 >= 0 && gg[r][c-1] == -1) {
                        ans[b]--;
                    } else {
                        ans[b] = -1;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

// https://leetcode.com/problems/where-will-the-ball-fall/
class Solution {
public:
    vector<int> findBall(const vector<vector<int>>& gg) {
        int h = gg.size();
        int w = gg[0].size();
        vector<int> ans(w);
        for (int i=0; i<w; i++)
            ans[i] = i;
        for (int r=0; r<h; r++) {
            for (int b=0; b<w; b++) {
                int c = ans[b];
                if (c >= 0) {
                    if (gg[r][c] == 1 && c+1 < w && gg[r][c+1] == 1) {
                        ans[b] = c+1;
                    } else if (gg[r][c] == -1 && c-1 >= 0 && gg[r][c-1] == -1) {
                        ans[b] = c-1;
                    } else {
                        ans[b] = -1;
                    }
                }
            }
        }
        return ans;
    }
};
