#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char **argv) {
	cout << "real answer" << endl;
	return 0;
}

/**
Welcome to Facebook!

This is just a simple shared plaintext pad, with no execution capabilities.

When you know what language you would like to use for your interview,
simply choose it from the dropdown in the top bar.

Enjoy your interview!
*/

/*

Print tree nodes in column order
  - Column: vertical columns, from left to right
  - Elements within a column: top to bottom

Input: binary tree

        6
       / \
      3   4
     / \   \
    5   1   0
     \     /
      2   8
     / \
    9   7
   /
  8

Output:

8  5  9  3  2  6  1  7  4  8  0
 */

#include <cstdio>
#include <vector>

struct Node {
    Node *left, *right;
    int val;
};

struct R {
    int cols2left;
};

R dfs_walk(const Node *root, int dep, int root_left, vector<vector<int>> &res) {
    if (root) {
        R l = dfs_walk(root->left, dep+1, root_left, res);
        R r = dfs_walk(root->right, dep+1, root_left + l.cols2left + 1, res);
        res[dep][l.cols2left] = root->val;
        return R {l.cols2left + 1};
    } else {
        return R {root_left};
    }
}

int main(int argc, char ** argv) {
    Node root = create_tree();
    vector<vector<int>> res(1000, vector<int>(1000, -1));
    dfs_walk(root, 0, 0, res);
    vetor<int> out;
    for (int c=0; c<1000; c++) {
        for (int r=999; r>= 0; r--) {
            if (res[r][c] != -1)
                out.push_back(res[r][c]);
        }
    }
    return 0;
}



/**
Welcome to Facebook!

This is just a simple shared plaintext pad, with no execution capabilities.

When you know what language you would like to use for your interview,
simply choose it from the dropdown in the top bar.

Enjoy your interview!
*/

/*

Print tree nodes in column order
  - Column: vertical columns, from left to right
  - Elements within a column: top to bottom

Input: binary tree

        6
       / \
      3   4
     / \   \
    5   1   0
     \     /
      2   8
     / \
    9   7
   /
  8

Output:

8  5  9  3  2  6  1  7  4  8  0
 */

#include <cstdio>
#include <vector>

struct Node {
    Node *left, *right;
    int val;
    int row, col;
    bool operator<(const Node &o) const {
        return col < o.col || (col == o.col && row < o.row);
    }
};

struct R {
    int cols2left;
};

R dfs_walk(Node *root, int dep, int root_left) {
    if (root) {
        R l = dfs_walk(root->left, dep+1, root_left, res);
        R r = dfs_walk(root->right, dep+1, root_left + l.cols2left + 1, res);
        root->row = dep;
        root->col = l.cols2left;
        return R {l.cols2left + 1};
    } else {
        return R {root_left};
    }
}

int main(int argc, char ** argv) {
    vector<Node> all_nodes;
    Node *root = read_tree(all_nodes, stdin);
    dfs_walk(root, 0, 0, res);
    vector<Node> srt_all_nodes(all_nodes);
    sort(srt_all_nodes.begin(), srt_all_nodes.end());
    vector<int> out;
    for (Node &n:srt_all_nodes) {
        out.push_back(n.val);
    }
    return 0;
}

