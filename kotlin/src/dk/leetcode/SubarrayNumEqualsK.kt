package dk.leetcode
// https://leetcode.com/problems/subarray-sum-equals-k/

private fun <T> MutableMap<T, Int>.inc(k: T) {
    val v = get(k) ?: 0
    put(k, v + 1)
}

class SubarrayNumEqualsK {
    fun subarraySum(nums: IntArray, k: Int): Int {
        val cnt = mutableMapOf<Int, Int>()
        var sm = 0
        cnt.inc(sm)
        var ans = 0
        nums.forEach { n ->
            sm += n
            ans += cnt[sm - k] ?: 0
            cnt.inc(sm)
        }
        return ans
    }
}