package dk.leetcode
// https://leetcode.com/problems/making-a-large-island/

class Solution_27 {
    private class Point(val x: Int, val y: Int) {
        operator fun plus(b: Point) = Point(x+b.x, y+b.y)
        fun inRange(range: Point) = x in 0 until range.x && y in 0 until range.y
    }

    private val MVs = arrayOf(Point(+1, 0), Point(-1, 0), Point(0, -1), Point(0, +1))

    private fun dfsPaint(p: Point, c: Int, dim: Point, grid: Array<IntArray>): Int {
        var sm = 1
        grid[p.y][p.x] = c
        for (mv in MVs) {
            val np = p + mv
            if (np.inRange(dim) && grid[np.y][np.x] == 1)
                sm += dfsPaint(np, c, dim, grid)
        }
        return sm
    }

    fun largestIsland(grid: Array<IntArray>): Int {
        val h = grid.size
        val w = grid[0].size
        val dim = Point(w, h)
        val colorCnt = arrayListOf(0, 0)
        var color = 2
        for (r in 0 until h)
            for (c in 0 until w)
                if (grid[r][c] == 1)
                    colorCnt.add(dfsPaint(Point(c,r), color++, dim, grid))
        var mx = -1
        for (r in 0 until h) {
            for (c in 0 until w) {
                if (grid[r][c] == 0) {
                    val aroundColors = mutableSetOf<Int>()
                    for (mv in MVs) {
                        val np = Point(c, r) + mv
                        if (np.inRange(dim))
                            aroundColors.add(grid[np.y][np.x])
                    }
                    val tot = 1 + aroundColors.map{ colorCnt[it] }.sum()
                    mx = maxOf(mx, tot)
                }
            }
        }
        if (mx == -1) // suki
            mx = h*w
        return mx
    }
}
