// https://leetcode.com/problems/can-place-flowers/

package dk.leetcode

class CanPlaceFlowers {
    fun canPlaceFlowers(fb: IntArray, n: Int): Boolean {
        val sz = fb.size
        var i = 0
        var last = -2
        var cnt = 0
        while (i < sz) {
            if (fb[i] == 0) {
                if (i - last > 2) {
                    last = i-1
                    cnt++
                }
            } else {
                last = i
            }
            i++
        }
        if (i - last > 2) {
            cnt++
        }
        return cnt >= n
    }
}