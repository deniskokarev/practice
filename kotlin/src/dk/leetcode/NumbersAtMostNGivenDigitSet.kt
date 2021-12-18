package dk.leetcode
// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
class NumbersAtMostNGivenDigitSet {
    // using c++ binary search behavior
    private inline fun CharArray.lowerBound(key: Char): Int {
        var b = 0
        var e = this.size
        while (b < e) {
            val m = b + (e-b)/2
            if (this[m] < key) {
                b = m + 1
            } else {
                e = m
            }
        }
        return b
    }
    fun atMostNGivenDigitSet(digits: Array<String>, n: Int): Int {
        val digs = digits.map{it[0]}.toCharArray()
        // DP on suffix
        val revNStr = n.toString().reversed()
        var pow = 1 // pow of digs.size
        // count of numbers less or equal on the given suffix
        // must optimistically start with 1
        // will turn to 0 when cannot make an LE number for the suffix
        var le = 1
        for (d in revNStr) {
            val ltDigsCnt = digs.lowerBound(d) // digs.filter{it<d}.count()
            le = if (ltDigsCnt < digs.size && digs[ltDigsCnt] == d) {
                // digs set contains d
                ltDigsCnt * pow + le
            } else {
                ltDigsCnt * pow
            }
            pow *= digs.size
        }
        // using geometric sequence sum formula
        // powSum = 1 + x + x^2 + x^3 +...+ x^n, where x=digs.size, n=revNStr.length
        // (only we won't need lowest 1 term in the answer)
        // there is also a special case for x = 1
        val powSum = if (digs.size > 1) {
            (pow - 1) / (digs.size - 1)
        } else {
            revNStr.length
        }
        // digits = [] scenario is also covered correctly with this -1
        return powSum - 1 + le
    }
}