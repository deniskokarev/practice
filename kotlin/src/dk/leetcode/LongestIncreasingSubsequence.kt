package dk.leetcode

class Solution_13 {
    private inline fun IntArray.lowerBound(sz: Int, k: Int): Int {
        var b = 0
        var e = sz
        while (b < e) {
            val m = b + (e-b)/2
            if (this[m] < k)
                b = m + 1
            else
                e = m
        }
        return b
    }
    fun lengthOfLIS(nums: IntArray): Int {
        val seq = IntArray(nums.size)
        var sz = 0
        nums.forEach {n ->
            val fndPos = seq.lowerBound(sz, n)
            if (fndPos == sz)
                seq[sz++] = n
            else
                seq[fndPos] = n
        }
        return sz
    }
}
