package dk.leetcode

class Solution_31 {
    fun minCut(s: String): Int {
        val sz = s.length
        // plX[f] - max palindrome length starting at f
        // means s[f..plX[f]] is palindrome, only we need to consider even and odd
        //     separately
        // ans[t+1] - best solution on prefix s[0..t]
        val pl = arrayOf(IntArray(sz), IntArray(sz) {1})
        val ans = IntArray(sz+1)
        ans[1] = 1
        for (t in 1 until sz) {
            ans[t+1] = ans[t]+1
            for (f in 0 until t) {
                if (s[f] == s[t]) {
                    val odd = (t-f+1) and 1
                    if (f + pl[odd][f+1] == t-1) {
                        pl[odd][f] = pl[odd][f+1] + 2
                        ans[t+1] = minOf(ans[t+1], ans[f] + 1)
                    }
                }
            }
        }
        return ans[sz]-1
    }
}
