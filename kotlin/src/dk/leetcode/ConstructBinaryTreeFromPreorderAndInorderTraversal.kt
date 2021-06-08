import dk.leetcode.TreeNode

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

class Solution {
    companion object {
        const val zeroVal = 3000
    }
    private fun buildTree(inorderVal2Pos: IntArray,
                          sz: Int,
                          preorder: IntArray,
                          preOfs: Int,
                          inorder: IntArray,
                          inOfs: Int): TreeNode? =
    if (sz == 0) {
        null
    } else {
        val rootVal = preorder[preOfs]
        val inorderRootOfs = inorderVal2Pos[rootVal + zeroVal]
        val szL = inorderRootOfs - inOfs
        val left = buildTree(inorderVal2Pos, szL, preorder, preOfs + 1, inorder, inOfs)
        val szR = sz - szL - 1
        val right = buildTree(inorderVal2Pos, szR, preorder, preOfs + 1 + szL, inorder, inorderRootOfs + 1)
        TreeNode(rootVal, left, right)
    }
    fun buildTree(preorder: IntArray, inorder: IntArray): TreeNode? {
        val inorderVal2Pos = IntArray(2 * zeroVal + 1)
        inorder.forEachIndexed { index, element -> inorderVal2Pos[element + zeroVal] = index }
        return buildTree(inorderVal2Pos, preorder.size, preorder, 0, inorder, 0)
    }
}