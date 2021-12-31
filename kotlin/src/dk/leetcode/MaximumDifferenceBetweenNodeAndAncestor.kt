package dk.leetcode
// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/

class MaximumDifferenceBetweenNodeAndAncestor {
    protected class MM(val mn: Int, val mx: Int) {
        inline fun combine(v: Int) = MM(minOf(mn, v), maxOf(mx, v))
        inline fun max(v: Int) = arrayOf(v - mn, mx - v, mx - v, v - mn).max()!!
    }

    protected fun fndMaxDiff(top: MM, root: TreeNode?): Int {
        if (root != null) {
            val s = top.max(root.`val`)
            val ntop = top.combine(root.`val`)
            val l = fndMaxDiff(ntop, root.left)
            val r = fndMaxDiff(ntop, root.right)
            return maxOf(s, l, r)
        } else {
            return 0
        }
    }

    fun maxAncestorDiff(root: TreeNode?) = fndMaxDiff(MM(root!!.`val`, root!!.`val`), root)
}