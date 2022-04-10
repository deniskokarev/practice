package dk.leetcode

// https://leetcode.com/problems/kth-largest-element-in-an-array/

import kotlin.random.Random

class Solution_KthLargestElementInArray {
    private inline fun IntArray.swap(i: Int, j: Int) {
        val t = this[i]
        this[i] = this[j]
        this[j] = t
    }

    /**
     * Partition array between [b, e) 3way based on pivot element originally located at position b
     * return Pair(first, second)
     * [b, first) < pivot
     * [first, second) = pivot
     * [second, e) > pivot
     */
    private inline fun IntArray.part3(b: Int, e: Int): Pair<Int, Int> {
        val pv = this[b]
        var m = b
        var i = b
        var j = e - 1
        while (i <= j) {
            if (this[i] < pv)
                swap(m++, i++)
            else if (this[i] > pv)
                swap(i, j--)
            else
                i++
        }
        return Pair(m, i)
    }

    fun findKthLargest(nums: IntArray, k: Int): Int {
        var b = 0
        var e = nums.size
        // since our part3 partitions the array in ASC order
        // we need to get the element at position invK
        val invK = nums.size - k
        // use randomized pivot to prevent n^2 attack
        val rnd = Random(1)
        while (true) {
            val p = b + rnd.nextInt(e - b)
            nums.swap(b, p)
            val (i, j) = nums.part3(b, e)
            if (invK < i)
                e = i
            else if (invK >= j)
                b = j
            else
                return nums[invK]
        }
    }
}
