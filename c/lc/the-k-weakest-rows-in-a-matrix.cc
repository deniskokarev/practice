// https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix
// cpu: O(h * log(w) + k * log(k))
// mem: O(k)

class Solution {
public:
    static vector<int> kWeakestRows(const vector<vector<int>>& mat, int k) {
        int h = mat.size();
        priority_queue<pair<int,int>> qq;
        for (int i=0; i<h; i++) {
            int p = upper_bound(begin(mat[i]), end(mat[i]), 1, greater<int>()) - begin(mat[i]);
            qq.push({p, i});
            if (qq.size() > k)
                qq.pop();
        }
        vector<int> res(k);
        for (int i = 0; i<k; i++) {
            res[i] = qq.top().second;
            qq.pop();
        }
        reverse(begin(res), end(res));
        return res;
    }
};

class Solution {
    int solders(const vector<int> &row) {
        int w = row.size();
        int f = 0, t = w;
        while (f < t) {
            int m = f + (t-f)/2;
            if (row[m])
                f = m + 1;
            else
                t = m;
        }
        return f;
    }
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        const int h = mat.size();
        vector<pair<int,int>> score(h);
        for (int r=0; r<h; r++)
            score[r] = {solders(mat[r]), r};
        nth_element(score.begin(), score.begin()+k-1, score.end());
        sort(score.begin(), score.begin()+k);
        vector<int> res(k);
        for (int i=0; i<k; i++)
            res[i] = score[i].second;
        return res;
    }
};
