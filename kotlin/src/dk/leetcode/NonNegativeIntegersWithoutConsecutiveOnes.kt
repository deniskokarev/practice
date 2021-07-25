package dk.leetcode
// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/

class Solution_22 {
    // subdivide conditions into 2 dimensions:
    // 1) only digits less_or_equal or any digit otherwise permitted,
    //    which becomes applicable when higher portion is strictly less
    // 2) actual digit chosen
    private var LE = 0
    private var ANY = 1

    private fun i2b(n: Int): IntArray {
        val b = IntArray(32)
        var ns = n
        for (i in b.indices) {
            b[i] = ns and 1
            ns = ns shr 1
        }
        return b
    }

    fun findIntegers(n: Int): Int {
        val bits = i2b(n)
        // dp[pos&1][le|any][0|1]:
        val dp = Array(2) { Array(2) { IntArray(2) } }
        dp[0][ANY][0] = 1
        dp[0][ANY][1] = 1
        if (bits[0] == 1) {
            dp[0][LE][0] = 1
            dp[0][LE][1] = 1
        } else {
            dp[0][LE][0] = 1
            dp[0][LE][1] = 0
        }
        for (i in 1 until bits.size) {
            val cur = i and 1
            val prev = cur xor 1
            dp[cur][ANY][0] = dp[prev][ANY][0] + dp[prev][ANY][1]
            dp[cur][ANY][1] = dp[prev][ANY][0]
            if (bits[i] == 1) {
                dp[cur][LE][0] = dp[prev][ANY][0] + dp[prev][ANY][1]
                dp[cur][LE][1] = dp[prev][LE][0]
            } else {
                dp[cur][LE][0] = dp[prev][LE][0] + dp[prev][LE][1]
                dp[cur][LE][1] = 0
            }
        }
        val lastPos = (bits.size+1) and 1
        return dp[lastPos][LE][0] + dp[lastPos][LE][1]
    }
}
