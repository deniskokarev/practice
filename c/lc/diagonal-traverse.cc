// crude, but working
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int h = matrix.size();
        if (!h)
            return res; // pidarasen
        int w = matrix[0].size();
        int d = +1;
        int x = 0, y = 0;
        while (x + y < w + h) {
            while (x >= 0 && y >= 0) {
                if (x < w && y < h)
                    res.push_back(matrix[y][x]);
                x += d;
                y -= d;
            }
            x = max(x, 0);
            y = max(y, 0);
            d = -d;
        }
        return res;
    }
};
