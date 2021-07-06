package dk.leetcode

// better solution if we had to return only L and R pointers in arr
// CPU = O(log(20000)*log(N)+k)
// where stupid k comes only from the expectation to get back the List
class Solution_10 {
    private fun IntArray.lowerBound(k: Int): Int {
        var f = 0
        var t = this.size
        while (f < t) {
            val m = (f + t) / 2
            if (this[m] < k)
                f = m + 1
            else
                t = m
        }
        return f
    }
    fun findClosestElements(arr: IntArray, k: Int, x: Int): List<Int> {
        // binary search for [x-delta..x+delta]
        var f = 0
        var t = 20_000
        // l,r - boundaries for count < k
        // L,R - boundaries for count >= k
        var (l, r) = Pair(f, t)
        var (L, R) = Pair(f, t)
        while (f <= t) {
            val m = (f+t)/2
            val fndL = arr.lowerBound(x-m)
            val fndR = arr.lowerBound(x+m+1)
            val num = fndR - fndL
            if (num < k) {
                l = fndL
                r = fndR
                f = m+1
            } else {
                L = fndL
                R = fndR
                t = m-1
            }
        }
        val num = R - L // >= k
        if (num > k) {
            val overR = R - r
            if (num - k < overR) {
                // discard only some rightmost extra elements
                R -= num-k
            } else {
                // discard all rightmost extra elements
                R = r
                // and some leftmost extra elements
                L = R - k
            }
        }
        return arr.slice(L until R).toList()
    }
}
