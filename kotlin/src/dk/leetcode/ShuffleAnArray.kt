package dk.leetcode

import kotlin.random.Random

class Solution_19(private val nums: IntArray) {
    private val sz = nums.size
    private val shuf = nums.clone()

    private inline fun IntArray.swap(i: Int, j: Int) {
        val t = this[i]
        this[i] = this[j]
        this[j] = t
    }

    /** Resets the array to its original configuration and return it. */
    fun reset(): IntArray {
        return nums
    }

    /** Returns a random shuffling of the array. */
    fun shuffle(): IntArray {
        for (i in nums.indices) {
            val p = Random.nextInt(i, sz)
            shuf.swap(i, p)
        }
        return shuf
    }
}
