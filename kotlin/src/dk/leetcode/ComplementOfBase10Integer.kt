package dk.leetcode
// https://leetcode.com/problems/complement-of-base-10-integer/
class ComplementOfBase10Integer {
    private companion object {
        val L2 = intArrayOf(
                       1,  1 shl 1,  1 shl 2,  1 shl 3,  1 shl 4,  1 shl 5,
                 1 shl 6,  1 shl 7,  1 shl 8,  1 shl 9, 1 shl 10, 1 shl 11,
                1 shl 12, 1 shl 13, 1 shl 14, 1 shl 15, 1 shl 16, 1 shl 17,
                1 shl 18, 1 shl 19, 1 shl 20, 1 shl 21, 1 shl 22, 1 shl 23,
                1 shl 24, 1 shl 25, 1 shl 26, 1 shl 27, 1 shl 28, 1 shl 29,
                1 shl 30
        )
    }

    // computing upper bound logarithm in O(log(log(N)))
    // @see https://github.com/deniskokarev/yalg/blob/master/include/ilog.hpp
    // optimized for C++
    private fun log2(n: Int): Int {
        var f = 0
        var t = L2.size
        while (f < t) {
            val m = (f + t) / 2
            if (n >= L2[m])
                f = m + 1
            else
                t = m
        }
        return f
    }

    fun bitwiseComplement(n: Int): Int {
        return if (n == 0) {
            1
        } else {
            val mask = (1 shl log2(n)) - 1
            n.inv() and mask
        }
    }
}
