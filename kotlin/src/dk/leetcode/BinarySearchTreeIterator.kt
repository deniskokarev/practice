package dk.leetcode
// https://leetcode.com/problems/binary-search-tree-iterator/

import java.util.*

class Solution_BSTIterator(root: TreeNode?) {

    val stack = Stack<TreeNode>()

    init {
        pushLeftBranch(root)
    }

    tailrec fun pushLeftBranch(root: TreeNode?) {
        if (root != null) {
            stack.add(root)
            pushLeftBranch(root.left)
        }
    }

    fun next(): Int {
        val top = stack.peek()
        stack.pop()
        pushLeftBranch(top.right)
        return top.`val`
    }

    fun hasNext() = stack.isNotEmpty()

}
