package dk.leetcode
// https://leetcode.com/problems/binary-tree-pruning/

class Solution_21 {
    fun pruneTree(root: TreeNode?): TreeNode? {
        if (root != null) {
            root.left = pruneTree(root.left)
            root.right = pruneTree(root.right)
            if (root.`val` != 1 && root.left == null && root.right == null)
                return null
        }
        return root
    }
}