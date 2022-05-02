package dk.leetcode
// https://leetcode.com/problems/sort-array-by-parity/

class SortArrayByParity_Solution {
    private inline fun odd(n: Int) = ((n and 1) == 1)

    private inline fun IntArray.swap(i: Int, j: Int) {
        val t = this[i]
        this[i] = this[j]
        this[j] = t
    }

    fun sortArrayByParity(nums: IntArray): IntArray {
        var i = 0
        var j = nums.size - 1
        while (i < j) {
            while (i < j && !odd(nums[i]))
                i++
            while (i < j && odd(nums[j]))
                j--
            nums.swap(i, j)
        }
        return nums
    }
}