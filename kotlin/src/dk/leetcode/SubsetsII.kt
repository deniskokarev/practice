package dk.leetcode
// https://leetcode.com/problems/subsets-ii/

class Solution_29 {
    private fun dfs(tgtList: MutableList<List<Int>>, tgt: MutableList<Int>, nums: IntArray, le: Int, pos: Int) {
        if (pos < 0) {
            tgtList.add(tgt.toList())
        } else {
            if (nums[pos] > le) {
                dfs(tgtList, tgt, nums, le, pos-1)
            } else {
                dfs(tgtList, tgt, nums, nums[pos]-1, pos-1)
                tgt.add(nums[pos])
                dfs(tgtList, tgt, nums, nums[pos], pos-1)
                tgt.removeAt(tgt.size-1) //tgt.removeLast()
            }
        }
    }
    fun subsetsWithDup(nums: IntArray): List<List<Int>> {
        nums.sort()
        val result = mutableListOf<List<Int>>()
        val tgt = mutableListOf<Int>()
        dfs(result, tgt, nums, Int.MAX_VALUE, nums.size-1)
        return result
    }
}
