package dk.leetcode

class Solution_32 {
    fun addStrings(num1: String, num2: String): String {
        val (n1, n2) = if (num1.length > num2.length)
            Pair(num1, num2)
        else
            Pair(num2, num1)
        val out = StringBuilder()
        var carry = 0
        var i = n1.length-1
        var j = n2.length-1
        while (j >= 0) {
            val d = (n1[i] - '0') + (n2[j] - '0') + carry
            carry = d / 10
            out.append(d % 10)
            i--
            j--
        }
        while (i >= 0) {
            val d = n1[i] - '0' + carry
            carry = d / 10
            out.append(d % 10)
            i--
        }
        if (carry > 0)
            out.append(1)
        out.reverse()
        return out.toString()
    }
}
