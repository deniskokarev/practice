class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int h = board.size();
        int w = board[0].size();
        board.push_back(vector<int>(w));
        vector<int> ourow(w); // O(width) mem for old upper row
        for (int r=0; r<h; r++) {
            int olc = 0; // old left char
            for (int c=0; c<w; c++) {
                int sm = olc;
                for (int x=max(c-1,0); x<min(c+2,w); x++) {
                    sm += ourow[x];
                    sm += board[r][x];
                    sm += board[r+1][x];
                }
                if (c) {
                    sm -= board[r][c-1];
                    ourow[c-1] = olc;
                }
                olc = board[r][c];
                board[r][c] = (sm == 3 || (olc && sm == 4));
            }
            ourow[w-1] = olc;
        }
        board.pop_back();
    }
};
