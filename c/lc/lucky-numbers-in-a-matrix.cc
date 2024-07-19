// https://leetcode.com/problems/lucky-numbers-in-a-matrix

// O(n+m) memory solution
class Solution {
    struct E {
        int v, i, j;
        bool operator<(const E &o) const {
            return i < o.i || i == o.i && j < o.j;
        }
    };
public:
    vector<int> luckyNumbers (const vector<vector<int>>& mm) {
        int h = mm.size();
        int w = mm[0].size();
        vector<E> r(h, {INT_MAX, -1, -1});
        vector<E> c(w, {INT_MIN, -1, -1});
        for (int i=0; i<h; i++) {
            for (int j=0; j<w; j++) {
                if (r[i].v > mm[i][j])
                    r[i] = {mm[i][j], i, j};
                if (c[j].v < mm[i][j])
                    c[j] = {mm[i][j], i, j};
            }
        }
        sort(begin(r), end(r));
        sort(begin(c), end(c));
        vector<int> res;
        int i = 0, j = 0;
        while (i < h && j < w) {
            if (r[i] < c[j]) {
                i++;
            } else if (c[j] < r[i]) {
                j++;
            } else {
                res.push_back(r[i].v);
                i++, j++;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& mm) {
        int h = mm.size();
        int w = mm[0].size();
        vector<vector<int>> sel(h, vector<int>(w));
        for (int i=0; i<h; i++) {
            int mn_idx = 0;
            for (int j=0; j<w; j++)
                if (mm[i][j] < mm[i][mn_idx])
                    mn_idx = j;
            sel[i][mn_idx] += 1;
        }
        for (int j=0; j<w; j++) {
            int mx_idx = 0;
            for (int i=0; i<h; i++)
                if (mm[i][j] > mm[mx_idx][j])
                    mx_idx = i;
            sel[mx_idx][j] += 1;
        }
        vector<int> ans;
        for (int i=0; i<h; i++)
            for (int j=0; j<w; j++)
                if (sel[i][j] > 1)
                    ans.push_back(mm[i][j]);
        return ans;
    }
};
