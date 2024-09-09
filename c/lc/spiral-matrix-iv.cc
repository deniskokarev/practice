// https://leetcode.com/problems/spiral-matrix-iv
class Solution {
    static const void fline(vector<vector<int>> &mm, int x, int y, int l, int dx, int dy, const ListNode *&h) {
        while (l--) {
            int v = -1;
            if (h) {
                v = h->val;
                h = h->next;
            }
            mm[y][x] = v;
            x += dx;
            y += dy;
        }
    }

    static const void fill(vector<vector<int>> &mm, const ListNode *&ll) {
        int h = mm.size();
        int w = mm[0].size();
        int x = 0;
        int y = 0;
        while (h > 1 && w > 1) {
            fline(mm, x, y, w - 1, +1, 0, ll);
            fline(mm, x + w - 1, y, h - 1, 0, +1, ll);
            fline(mm, x + w - 1, y + h - 1, w - 1, -1, 0, ll);
            fline(mm, x, y + h - 1, h - 1, 0, -1, ll);
            h -= 2;
            w -= 2;
            x++, y++;
        }
        if (w == 1) {
            fline(mm, x, y, h, 0, +1, ll);
        } else if (h == 1) {
            fline(mm, x, y, w, +1, 0, ll);
        }
    }

public:
    static vector<vector<int>> spiralMatrix(int m, int n, const ListNode *h) {
        vector<vector<int>> mm(m, vector<int>(n));
        fill(mm, h);
        return mm;
    }
};

