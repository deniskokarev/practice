package dk.leetcode

class Solution_36 {
    class F(val pt: Int, val mxD: Int, val mxK: Char) // fold accumulator

    fun slowestKey(releaseTimes: IntArray, keysPressed: String) =
        releaseTimes.zip(keysPressed.asIterable()).fold(F(0, -1, ' ')) { f, e ->
            val t = e.first
            val c = e.second
            val d = t - f.pt
            if (f.mxD < d || f.mxD == d && f.mxK < c) F(t, d, c)
            else F(t, f.mxD, f.mxK)
        }.mxK
}
