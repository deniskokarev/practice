package dk.leetcode
// https://leetcode.com/problems/3sum-closest/

import kotlin.math.abs

class Solution_24 {
    fun threeSumClosest(nums: IntArray, target: Int): Int {
        val sz = nums.size
        nums.sort()
        var best = 1_000_000_000
        for (i in 0 until sz-2) {
            var j = i + 1
            var k = sz - 1
            while (j < k) {
                val sm = nums[i] + nums[j] + nums[k]
                if (abs(sm - target) < abs(best - target))
                    best = sm
                if (sm >= target)
                    k--
                else
                    j++
            }
        }
        return best
    }
}