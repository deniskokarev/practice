package dk.leetcode

class Solution_9 {
    private class R(val ans: TreeNode?, val cnt: Int) {}
    private fun dfs(root: TreeNode?, either: List<TreeNode?>): R {
        if (root != null) {
            val l = dfs(root.left, either)
            val r = dfs(root.right, either)
            return when {
                (l.cnt == 2) -> l
                (r.cnt == 2) -> r
                (l.cnt == 1 && r.cnt == 1) -> R(root, 2)
                (l.cnt == 1 && root in either) -> R(root, 2)
                (r.cnt == 1 && root in either) -> R(root, 2)
                (root in either) -> R(null, 1)
                (l.cnt == 1) -> l
                (r.cnt == 1) -> r
                else -> R(null, 0)
            }
        } else {
            return R(null, 0);
        }
    }
    fun lowestCommonAncestor(root: TreeNode?, p: TreeNode?, q: TreeNode?): TreeNode? {
        return dfs(root, listOf(p, q)).ans
    }
}

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
