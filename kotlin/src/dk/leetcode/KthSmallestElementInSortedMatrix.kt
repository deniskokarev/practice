package dk.leetcode

// binary search in each row will work better in Cols >> Rows scenario
// written in functional style
class Solution_12 {
    private tailrec fun IntArray.upperBound(begin: Int, end: Int, k: Int): Int = when {
        (begin == end) -> begin
        else -> {
            val m = begin + (end - begin) / 2
            when {
                (this[m] <= k) -> upperBound(m + 1, end, k)
                else -> upperBound(begin, m, k)
            }
        }
    }

    private tailrec fun Array<IntArray>.cntLE(sm: Int, row: Int, end: Int, k: Int): Int = when {
        (row == this.size) -> sm
        (end == 0) -> sm
        else -> {
            val newEnd = this[row].upperBound(0, end, k)
            cntLE(sm+newEnd, row+1, newEnd, k)
        }
    }

    private tailrec fun Array<IntArray>.cntLE(k: Int): Int = cntLE(0, 0, this[0].size, k)

    private tailrec fun Array<IntArray>.lowerBoundKthSmallest(begin: Int, end: Int, nth: Int): Int = when {
        (begin == end) -> begin
        else -> {
            val m = begin + (end - begin) / 2
            when {
                (cntLE(m) < nth) -> lowerBoundKthSmallest(m + 1, end, nth)
                else -> lowerBoundKthSmallest(begin, m, nth)
            }
        }
    }

    fun kthSmallest(matrix: Array<IntArray>, nth: Int) = matrix.lowerBoundKthSmallest(matrix[0][0], matrix.last().last(), nth)
}
