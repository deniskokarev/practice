// O(n*n*log^2(n)) for https://leetcode.com/problems/construct-quad-tree/
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
    struct P {
        int x, y;
    };
    int sum(const vector<vector<int>>& grid, const P &tl, int sz) {
        int sm = 0;
        for (int r=tl.y; r<tl.y+sz; r++)
            for (int c=tl.x; c<tl.x+sz; c++)
                sm += grid[r][c];
        return sm;
    }
    Node* construct(const vector<vector<int>>& grid, const P &tl, int sz) {
        assert((sz & (sz-1)) == 0 && "sz must be a power of 2");
        int sm = sum(grid, tl, sz);
        if (sm == sz*sz) {
            return new Node(1, true);
        } else if (sm == 0) {
            return new Node(0, true);
        } else {
            auto ntl = construct(grid, tl, sz/2);
            auto ntr = construct(grid, P{tl.x+sz/2, tl.y}, sz/2);
            auto nbl = construct(grid, P{tl.x, tl.y+sz/2}, sz/2);
            auto nbr = construct(grid, P{tl.x+sz/2, tl.y+sz/2}, sz/2);
            return new Node(0, false, ntl, ntr, nbl, nbr);
        }
    }
public:
    Node* construct(const vector<vector<int>>& grid) {
        int sz = grid.size();
        return construct(grid, P{0,0}, sz);
    }
};
