package dk.leetcode

class ThreeEqualParts_Solution {
    fun threeEqualParts(arr: IntArray): IntArray {
        val sz = arr.size
        val nextOnePos = IntArray(sz)
        var onePos = arr.size
        for (p in arr.size-1 downTo 0) {
            if (arr[p] == 1)
                onePos = p
            nextOnePos[p] = onePos
        }
        // [b1,e1) + [b2,e2) + [b3,e3)
        val b1 = nextOnePos[0]
        if (b1 == sz)
            return intArrayOf(0, 2) // WTF?
        for (e1 in b1 + 1 until sz) {
            val len = e1 - b1
            val b2 = nextOnePos[e1]
            val e2 = b2 + len
            if (e2 >= sz)
                break
            val b3 = nextOnePos[e2]
            val e3 = b3 + len
            if (e3 > sz)
                break
            if (e3 == sz) {
                val a1 = arr.slice(b1 until e1)
                val a2 = arr.slice(b2 until e2)
                val a3 = arr.slice(b3 until e3)
                if (a1 == a2 && a2 == a3)
                    return intArrayOf(e1-1, e2)
                else
                    break
            }
        }
        return intArrayOf(-1, -1)
    }
}