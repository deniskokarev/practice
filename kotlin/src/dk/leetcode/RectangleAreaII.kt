package dk.leetcode

// https://leetcode.com/problems/rectangle-area-ii/
/**
 * CPU: O(N*N)
 * MEM: O(N*N)
 * where N - number of rectangles
 * Map coordinates to more compact grid
 * Using 2D Fenwick tree to build 2D barchart, where each cell's height indicating number of rectangles covering it
 * (although, we don't care about the height, only care if coverage is > 0)
 * Adding each rectangle is log(N)*log(N), making this step O(N*log(N)*log(N))
 * Then we could query the height of each cell in log(N)*log(N) for each cell
 * or recompute the height of all cells in N*N. Thus the overall complexity is
 * N*N
 */
// I miss C++ templating
internal class IntFW(val fw: IntArray) {
    val sz = fw.size
    inline fun add(pos: Int, d: Int) {
        var p = pos
        while (p < sz) {
            fw[p] += d
            p = p or (p + 1)
        }
    }

    inline fun sum(pos: Int): Int {
        var p = pos
        var sm = 0
        while (p >= 0) {
            sm += fw[p]
            p = (p and (p + 1)) - 1
        }
        return sm
    }
}

// I miss C++ templating
internal class FW2D(val fw: Array<IntFW>) {
    val sz = fw.size
    inline fun add(row: Int, col: Int, d: Int) {
        var p = row
        while (p < sz) {
            fw[p].add(col, d)
            p = p or (p + 1)
        }
    }

    inline fun sum(row: Int, col: Int): Int {
        var p = row
        var sm = 0
        while (p >= 0) {
            sm += fw[p].sum(col)
            p = (p and (p + 1)) - 1
        }
        return sm
    }
}

internal class BarChart2D(val rows: Int, val cols: Int) {
    class P(val row: Int, val col: Int)

    private val fw2d = FW2D(Array(rows) { IntFW(IntArray(cols)) })

    // increment heights by d for all points of the rectangle
    // O(log(rows)*log(cols)) - i.e. doesn't depend on rectangle area
    // depends just on overall barchart size
    fun addHeight(bl: P, tr: P, d: Int) {
        fw2d.add(tr.row, tr.col, d)
        fw2d.add(tr.row, bl.col, -d)
        fw2d.add(bl.row, tr.col, -d)
        fw2d.add(bl.row, bl.col, d)
    }

    // probe the height at one point in O(log(rows)*log(cols))
    fun getHeight(p: P) = fw2d.sum(p.row, p.col)

    // recompute all heights on barchart in rows*cols
    // @return matrix with 1-based indexes
    fun materialize2D(): Array<IntArray> {
        val res = Array(rows + 1) { IntArray(cols + 1) }
        val sub = Array(rows * 2 + 1) { IntArray(cols * 2 + 1) } // to avoid checking borders
        for (r in 0 until rows) {
            val pr = r or (r + 1)
            for (c in 0 until cols) {
                val pc = c or (c + 1)
                res[r + 1][c + 1] = fw2d.fw[r].fw[c]
                sub[r + 1][pc + 1] += res[r + 1][c + 1]
                sub[pr + 1][c + 1] += res[r + 1][c + 1]
                sub[pr + 1][pc + 1] -= res[r + 1][c + 1]
                res[r + 1][c + 1] -= sub[r + 1][c + 1]
                res[r + 1][c + 1] += res[r + 1][c]
                res[r + 1][c + 1] += res[r][c + 1]
                res[r + 1][c + 1] -= res[r][c]
            }
        }
        return res
    }
}

// I miss C++ STL
internal inline fun IntArray.lowerBound(v: Int): Int {
    val a = this
    var f = 0
    var t = a.size
    while (f < t) {
        val m = f + (t - f) / 2
        if (a[m] < v)
            f = m + 1
        else
            t = m
    }
    return f
}

// I miss C++ STL
internal inline fun IntArray.uniq(): Int {
    val a = this
    val sz = a.size
    var i = 1
    var j = 1
    while (j < sz) {
        if (a[j - 1] != a[j])
            a[i++] = a[j++]
        else
            j++
    }
    return i
}

class Solution_34 {
    private enum class XY {
        X,
        Y
    }

    // "normalize" coordinates to squeeze them to smaller grid
    private fun squeezeCoordinates(rectangles: Array<IntArray>, ofs: Int): IntArray {
        val vv = IntArray(2 * rectangles.size)
        rectangles.forEachIndexed { i, r ->
            vv[2 * i] = r[ofs]
            vv[2 * i + 1] = r[ofs + 2]
        }
        vv.sort()
        val sz = vv.uniq()
        return IntArray(sz) { i -> vv[i] }
    }

    private inline fun rectToCompactCoordinates(rectangle: IntArray, x: IntArray, y: IntArray) =
        Pair(
            BarChart2D.P(y.lowerBound(rectangle[1]), x.lowerBound(rectangle[0])),
            BarChart2D.P(y.lowerBound(rectangle[3]), x.lowerBound(rectangle[2]))
        )

    fun rectangleArea(rectangles: Array<IntArray>): Int {
        val x = squeezeCoordinates(rectangles, XY.X.ordinal)
        val y = squeezeCoordinates(rectangles, XY.Y.ordinal)
        val g = BarChart2D(y.size, x.size)
        rectangles.forEach { r ->
            val (bl, tr) = rectToCompactCoordinates(r, x, y)
            g.addHeight(bl, tr, 1)
        }
        var sm = 0L
        var out = g.materialize2D()
        for (r in 0 until y.size - 1) {
            for (c in 0 until x.size - 1) {
                if (out[r + 1][c + 1] > 0) {
                    val w = (x[c + 1] - x[c]).toLong()
                    val h = (y[r + 1] - y[r]).toLong()
                    sm += h * w
                }
            }
        }
        return (sm % 1_000_000_007L).toInt()
    }
}
