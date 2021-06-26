package dk.leetcode

class Solution_7 {
    // fenwick tree
    class Fw(private val sz: Int) {
        private val fw = IntArray(sz)
        fun inc(pos: Int, inc: Int) {
            var p = pos
            while (p < sz) {
                fw[p] += inc
                p = p or (p+1)
            }
        }
        fun sum(pos: Int): Int {
            var sm = 0
            var p = pos
            while (p >= 0) {
                sm += fw[p]
                p = (p and (p+1)) - 1
            }
            return sm
        }
    }
    companion object {
        private const val HMX = 10000 // "half" of max
    }
    fun countSmaller(nums: IntArray): List<Int> {
        val fw = Fw(2*HMX+1)
        for (i in nums.lastIndex downTo 0) {
            fw.inc(nums[i]+HMX, 1)
            nums[i] = fw.sum(nums[i]+HMX-1)
        }
        return nums.toList()
    }
}
