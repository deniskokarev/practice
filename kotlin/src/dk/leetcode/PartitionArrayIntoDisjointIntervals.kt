package dk.leetcode

// TODO: find O(1) space solution
class Solution_20 {
    fun partitionDisjoint(nums: IntArray): Int {
        val mnr = nums.clone()
        val sz = nums.size
        for (p in sz-2 downTo 0)
            mnr[p] = minOf(mnr[p], mnr[p+1])
        var mx = -1
        for (i in 0 until sz-1) {
            mx = maxOf(mx, nums[i])
            if (mx <= mnr[i+1])
                return i+1
        }
        return -1
    }
}