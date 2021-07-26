package dk.leetcode
// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

class Solution_23 {
    private fun sortedArrayToBST(nums: IntArray, b: Int, e: Int): TreeNode? =
        if (b < e) {
            val mid = b + (e - b) / 2
            val left = sortedArrayToBST(nums, b, mid)
            val right = sortedArrayToBST(nums, mid + 1, e)
            TreeNode(nums[mid], left, right)
        } else {
            null
        }

    fun sortedArrayToBST(nums: IntArray) = sortedArrayToBST(nums, 0, nums.size)
}
