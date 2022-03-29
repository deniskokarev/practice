package dk.leetcode

// https://leetcode.com/problems/find-the-duplicate-number/

class Solution_FindTheDuplicateNumber {
    fun findDuplicate(nums: IntArray): Int {
        var fnd = -1
        for (i in nums.indices) {
            var j = i
            while (nums[j] > 0) {
                fnd = nums[j]
                nums[j] = -nums[j]
                j = -nums[j] - 1
            }
            if (j != i) {
                break
            }
        }
        for (i in nums.indices) {
            if (nums[i] < 0)
                nums[i] = -nums[i]
        }
        return fnd
    }
}