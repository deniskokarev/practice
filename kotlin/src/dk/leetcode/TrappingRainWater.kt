package dk.leetcode

class Solution_26 {
    fun trap(height: IntArray): Int {
        if (height.size < 2)
            return 0
        var l = 0
        var r = height.size - 1
        var mxL = -1
        var mxR = -1
        var origL = 0
        var origR = 0
        var floodL = 0
        var floodR = 0
        while (l < r) {
            if (height[l] < height[r]) {
                origL += height[l]
                mxL = maxOf(mxL, height[l])
                floodL += mxL
                l++
            } else {
                origR += height[r]
                mxR = maxOf(mxR, height[r])
                floodR += mxR
                r--
            }
        }
        return floodL + floodR - origL - origR
    }
}
