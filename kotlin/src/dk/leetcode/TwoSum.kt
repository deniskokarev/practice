package dk.leetcode
// https://leetcode.com/problems/two-sum/

class Solution_28 {
    fun twoSum(nums: IntArray, target: Int): IntArray {
        val seen = mutableMapOf<Int,Int>()
        nums.forEachIndexed{ idx, v ->
            val fnd = seen[target-v]
            if (fnd != null)
                return intArrayOf(fnd, idx)
            seen[v] = idx
        }
        return intArrayOf(0, 0)
    }
}
