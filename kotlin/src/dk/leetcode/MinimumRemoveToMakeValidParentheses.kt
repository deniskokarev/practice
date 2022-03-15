package dk.leetcode
// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

private fun <T> MutableList<T>.pop() {
    removeAt(lastIndex)
}

class Solution_srcMinimumRemoveToMakeValidParentheses {
    fun minRemoveToMakeValid(s: String): String {
        var cnt = 0
        var sm = 0
        val sz = s.length
        val rm = mutableListOf<Int>()
        val stack = mutableListOf<Int>()
        for (i in s.indices) {
            val d =
                    when (s[i]) {
                        '(' -> +1
                        ')' -> -1
                        else -> 0
                    }
            cnt += d
            if (d > 0) {
                stack.add(i)
            } else if (d < 0) {
                if (stack.isNotEmpty()) {
                    stack.pop()
                }
                if (cnt < 0) {
                    rm.add(i)
                    cnt = 0
                }
            }
        }
        rm.addAll(stack)
        val ch = s.toCharArray()
        rm.forEach { i -> ch[i] = ' ' }
        val ans = ch.filter { c -> c != ' ' }.joinToString("")
        return ans
    }
}
