package dk.leetcode

class Solution_8 {
    private class N(val node: TreeNode, val parent: Int, val lvl: Int) {}
    private fun dfsFlattenInOrder(dst: ArrayList<N>, parent: Int, lvl: Int, root: TreeNode?) {
        if (root != null) {
            val nid = dst.size
            dst.add(N(root, parent, lvl))
            dfsFlattenInOrder(dst, nid, lvl + 1, root.left)
            dfsFlattenInOrder(dst, nid, lvl + 1, root.right)
        }
    }
    fun lowestCommonAncestor(root: TreeNode?, p: TreeNode?, q: TreeNode?): TreeNode? {
        val tree = ArrayList<N>()
        dfsFlattenInOrder(tree, 0, 0, root)
        var pn = -1
        var qn = -1
        tree.forEachIndexed { idx, n ->
            when {
                (n.node === p) -> pn = idx
                (n.node === q) -> qn = idx
            }
        }
        if (tree[pn].lvl > tree[qn].lvl) {
            // no swap in kt
            val a = pn
            pn = qn
            qn = a
        }
        while (tree[pn].lvl < tree[qn].lvl)
            qn = tree[qn].parent
        while (pn != qn) {
            pn = tree[pn].parent
            qn = tree[qn].parent
        }
        return tree[pn].node
    }
}
