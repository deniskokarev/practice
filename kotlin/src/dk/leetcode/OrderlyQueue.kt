package dk.leetcode

class Solution_35 {
    fun orderlyQueue(s: String, k: Int): String {
        if (k == 1) {
            val s2 = s + s
            val sz = s.length
            var mnStr = s
            for (i in 1 until sz) {
                val s1 = s2.substring(i, i+sz)
                if (s1 < mnStr)
                    mnStr = s1
            }
            return mnStr
        } else {
            // as soon as we can flip order of 2 adjacent elements we can sort
            val c = s.toCharArray()
            c.sort()
            return String(c)
        }
    }
}
