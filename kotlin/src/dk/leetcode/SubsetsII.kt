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

// usage-friendly generator approach
// async, but slower than above - each iteration the control and the value must go via layers of yieldAll()
class Solution_29co {
    private fun coDFS(tgt: MutableList<Int>, nums: IntArray, le: Int, pos: Int): Sequence<List<Int>> = sequence {
        if (pos < 0) {
            yield(tgt.toList())
        } else {
            if (nums[pos] > le) {
                yieldAll(coDFS(tgt, nums, le, pos-1))
            } else {
                yieldAll(coDFS(tgt, nums, nums[pos]-1, pos-1))
                tgt.add(nums[pos])
                yieldAll(coDFS(tgt, nums, nums[pos], pos-1))
                tgt.removeAt(tgt.size-1) //tgt.removeLast()
            }
        }
    }
    fun subsetsWithDup(nums: IntArray): List<List<Int>> {
        nums.sort()
        val tgt = mutableListOf<Int>()
        return coDFS(tgt, nums, Int.MAX_VALUE, nums.size - 1).toList()
    }
}
