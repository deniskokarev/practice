package dk.leetcode

class Solution_5 {
    fun generate(numRows: Int): List<List<Int>> {
        val res = List(numRows) { MutableList(it+1) {1} }
        val rowIt = res.iterator()
        var currRow = rowIt.next()
        for (nrow in 1 until numRows) {
            val prevRow = currRow
            currRow = rowIt.next()
            val prevColIt = prevRow.iterator()
            var p1 = 0
            val currColIt = currRow.listIterator()
            for (i in 0 until nrow) {
                val p0 = p1
                p1 = prevColIt.next()
                currColIt.next()
                currColIt.set(p0+p1)
            }
        }
        return res
    }
}