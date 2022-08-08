def solution(s):
    rcnt = 0
    ans = 0
    for c in s:
        if c == '>':
            rcnt += 1
        elif c == '<':
            ans += rcnt
    return 2 * ans
        

print solution("--->-><-><-->-")
print solution(">----<")
print solution("<<>><")





    
