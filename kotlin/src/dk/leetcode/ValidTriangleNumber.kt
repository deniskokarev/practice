package dk.leetcode

class Solution_16 {
    private tailrec fun IntArray.lowerBound(f: Int, t: Int, k: Int): Int {
        return if (f < t) {
            val m = f + (t - f) / 2
            if (this[m] < k)
                lowerBound(m + 1, t, k)
            else
                lowerBound(f, m, k)
        } else {
            f
        }
    }
    fun triangleNumber(nums: IntArray): Int {
        val sz = nums.size
        nums.sort()
        var cnt = 0
        var i = 0
        while (i < sz && nums[i] == 0)  // suki
            i++
        while (i < sz-2) {
            var j = i + 1
            // we take (i + j..k)
            var k = nums.lowerBound(j+1, sz, nums[i]+nums[j])
            while (j < sz-1 && k < sz) {
                while (k < sz && nums[i] + nums[j] > nums[k])
                    k++
                cnt += k - j - 1
                j++
            }
            val r = sz - j
            cnt += r * (r - 1) / 2   // shortcut when k hits the wall
            i++
        }
        return cnt
    }
}
