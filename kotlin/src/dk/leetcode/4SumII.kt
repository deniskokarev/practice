// https://leetcode.com/problems/4sum-ii/
package dk.leetcode

private fun <K> MutableMap<K, Int>.increment(key: K) {
    putIfAbsent(key, 0)
    this[key] = this[key]!! + 1
}

class `4SumII` {
    fun fourSumCount(nums1: IntArray, nums2: IntArray, nums3: IntArray, nums4: IntArray): Int {
        val sm12 = hashMapOf(0 to 0)
        for (i in nums1.indices) {
            for (j in nums2.indices) {
                sm12.increment(nums1[i]+nums2[j])
            }
        }
        var cnt = 0
        for (i in nums3.indices) {
            for (j in nums4.indices) {
                val s = nums3[i]+nums4[j]
                cnt += sm12.get(-s)?:0
            }
        }
        return cnt
    }
}
