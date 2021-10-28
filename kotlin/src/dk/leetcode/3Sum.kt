package dk.leetcode

class Solution_20211028 {
    fun threeSum(nums: IntArray): List<List<Int>> {
        val res = mutableListOf<List<Int>>()
        val aa = nums.sorted()
        val sz = aa.size
        var i = 0
        while (i < sz - 2) {
            var j = i + 1
            var k = sz - 1
            while (j < k) {
                if (aa[i] + aa[j] + aa[k] > 0) {
                    k--
                } else if (aa[i] + aa[j] + aa[k] < 0) {
                    j++
                } else {
                    res.add(listOf(aa[i], aa[j], aa[k]))
                    while (j + 1 < k && aa[j] == aa[j + 1])
                        j++
                    j++
                }
            }
            while (i + 1 < sz - 2 && aa[i] == aa[i + 1])
                i++
            i++
        }
        return res
    }
}
