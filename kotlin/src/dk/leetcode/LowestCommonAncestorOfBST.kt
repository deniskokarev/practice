package dk.leetcode

class Solution_18 {
    private tailrec fun lca(root: TreeNode, mn: Int, mx: Int): TreeNode = when {
        (mx < root.`val`) -> lca(root.left!!, mn, mx)
        (mn > root.`val`) -> lca(root.right!!, mn, mx)
        else -> root
    }
    fun lowestCommonAncestor(root: TreeNode?, p: TreeNode?, q: TreeNode?): TreeNode? {
        val (mn, mx) = Pair(minOf(p!!.`val`, q!!.`val`), maxOf(p!!.`val`, q!!.`val`))
        return lca(root!!, mn, mx)
    }
}
