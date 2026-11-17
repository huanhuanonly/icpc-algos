# 蓝桥杯省赛自测（Python B 组）
# 
# => P16267 [蓝桥杯 2026 省 Python B 组] 位数求和 ( @c 普及+/提高 )
# 
# -> https://www.luogu.com.cn/problem/P16267
# 
# Submissions ~> https://www.luogu.com.cn/record/273892271 By huanhuanonly
# 
# @b Monotonic-stack and @b Classification-discussion
# 
# ----April 13, 2026 [20h:49m:27s]----

n = int(input())
v = list(map(int, input().split()))

mod = 998244353

l, r = [-1] * n, [n] * n
stack = []

for i in range(n):

    while stack and v[stack[-1]] < v[i]:
        stack.pop()

    l[i] = stack[-1] if stack else -1

    stack.append(i)

stack.clear()

for i in range(n - 1, -1, -1):

    while stack and v[stack[-1]] <= v[i]:
        stack.pop()

    r[i] = stack[-1] if stack else n

    stack.append(i)


def calc(cl, cr, m):
    if cl > cr:
        cl, cr = cr, cl

    if m >= cl + cr - 1:
        return cl * cr
    elif m <= cl:
        return m * (m + 1) // 2
    elif m >= cr:
        t = cl + cr - m - 1
        return cl * cr - t * (t + 1) // 2
    else:
        return m * (m + 1) // 2 - (m - cl) * (m - cl + 1) // 2

ans = 0

for f in range(1, 6 + 1):
    lo = 10 ** (f - 1)
    hi = 10 ** f - 1

    for i in range(n):
        cl = i - l[i]
        cr = r[i] - i

        ans += (calc(cl, cr, hi) + mod - calc(cl, cr, lo - 1)) * f * v[i] % mod
        ans %= mod

print(ans)
