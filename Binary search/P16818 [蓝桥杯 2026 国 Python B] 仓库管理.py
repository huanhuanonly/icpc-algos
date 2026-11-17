# => P16818 [蓝桥杯 2026 国 Python B] 仓库管理 ( @c 普及/提高− )
#
# -> https://www.luogu.com.cn/problem/P16818
#
# Submissions ~> https://www.luogu.com.cn/record/281263257 By huanhuanonly
#
# @b Binary-search
#
# ----June 09, 2026 [01h:18m:09s]----

n, m, L, R = map(int, input().split())

def check(mid):
    minsum = 0
    rem = n

    for i in range(m):
        t = min(mid, rem)
        minsum += t * (i + 1)
        rem -= t

    maxsum = 0
    rem = n

    for i in range(m - 1, -1, -1):
        t = min(mid, rem)
        maxsum += t * (i + 1)
        rem -= t

    return minsum <= L <= maxsum or minsum <= R <= maxsum

l, r = 0, n + 1

while r - l > 1:
    mid = l + r >> 1

    if check(mid):
        r = mid
    else:
        l = mid

if r == n + 1:
    print(-1)
else:
    print(r)