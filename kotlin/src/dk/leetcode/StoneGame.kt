package dk.leetcode

class Solution_30 {
    fun stoneGame(piles: IntArray): Boolean {
        val sz = piles.size
        // dp[len_1][f] - best resulting score of 1st player
        // on the interval [f..f+len_1]
        // except we need only 2 rows in length dimension
        val dp = arrayOf(piles.clone(), IntArray(sz))
        for (len_1 in 1 until sz) {
            val dpLen = dp[len_1 and 1]
            val dpPrevLen = dp[(len_1+1) and 1]
            for (f in 0 until sz - len_1)
                dpLen[f] = maxOf(piles[f] - dpPrevLen[f + 1], piles[f + len_1] - dpPrevLen[f])
        }
        return dp[(sz+1) and 1][0] > 0
    }
}

class Solution_30_wow {
    fun stoneGame(piles: IntArray): Boolean {
        return true
    }
}
