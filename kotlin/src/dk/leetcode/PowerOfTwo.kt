package dk.leetcode
// https://leetcode.com/problems/power-of-two/
class PowerOfTwo {
    fun isPowerOfTwo(n: Int) =
            (n > 0) && (n and (n-1) == 0)
}