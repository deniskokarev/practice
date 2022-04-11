package dk.leetcode
// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

private fun <T> MutableList<T>.pop() {
    removeAt(lastIndex)
}

class Solution_srcMinimumRemoveToMakeValidParentheses {
    fun minRemoveToMakeValid(s: String): String {
        val rm = mutableSetOf<Int>()
        val stack = mutableListOf<Int>()
        for (i in s.indices) {
            if (s[i] == '(') {
                stack.add(i)
            } else if (s[i] == ')') {
                if (stack.isNotEmpty()) {
                    stack.pop()
                } else {
                    rm.add(i)
                }
            }
        }
        rm.addAll(stack)
        return s.filterIndexed { i, _ -> !rm.contains(i) }
    }
}
