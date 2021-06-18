package dk.leetcode

class NumArray(private val nums: IntArray) {
    private val fw = IntArray(nums.size+1)
    private val fwsz = fw.size
    init {
        nums.forEachIndexed { idx, inc -> fwInc(idx, inc) }
    }
    private fun fwInc(pos: Int, inc: Int) {
        var p = pos+1
        while (p < fwsz) {
            fw[p] += inc
            p = p or (p+1)
        }
    }
    private fun fwSum(pos: Int): Int {
        var p = pos+1
        var sm = 0
        while (p >= 0) {
            sm += fw[p]
            p = (p and (p+1)) - 1
        }
        return sm
    }
    fun update(idx: Int, v: Int) {
        val inc = v - nums[idx]
        nums[idx] = v
        fwInc(idx, inc)
    }
    fun sumRange(left: Int, right: Int) = fwSum(right) - fwSum(left-1)
}
