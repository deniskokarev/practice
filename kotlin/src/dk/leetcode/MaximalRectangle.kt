package dk.leetcode
// https://leetcode.com/problems/maximal-rectangle/
class MaximalRectangle {
    private class H(val h: Int, val c: Int)

    // LC kotlin is so old that it doesn't even have removeLast()
    private fun <T> ArrayList<T>.pop() {
        this.removeAt(this.lastIndex)
    }

    private fun maxRect(mat: Array<Array<Int>>, r: Int): Int {
        val w = mat[r].size
        val ht = arrayListOf(H(mat[r][0], 0))
        var mx = 0
        for (c in 1 until w) {
            var lastC = c
            while (ht.isNotEmpty() && mat[r][c] < ht.last().h) {
                lastC = ht.last().c
                mx = Math.max(mx, (c - lastC) * ht.last().h)
                ht.pop()
            }
            ht.add(H(mat[r][c], lastC))
        }
        while (ht.isNotEmpty()) {
            mx = Math.max(mx, (w - ht.last().c) * ht.last().h)
            ht.pop()
        }
        return mx
    }

    fun maximalRectangle(matrix: Array<CharArray>): Int {
        val h = matrix.size
        val w = matrix[0].size
        val mat = Array(h) { r -> Array(w) { c -> matrix[r][c] - '0' } }
        for (r in 1 until h)
            for (c in 0 until w)
                mat[r][c] = (mat[r - 1][c] + 1) * mat[r][c]
        var mx = 0
        for (r in 0 until h)
            mx = Math.max(mx, maxRect(mat, r))
        return mx
    }
}
