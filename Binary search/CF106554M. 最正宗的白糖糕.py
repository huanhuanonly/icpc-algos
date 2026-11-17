# [Unofficial Mirror] 2026 CCPC National Invitational (Nanchang) and The 3rd Jiangxi Provincial Programming Contest
#
# => M. 最正宗的白糖糕
#
# -> https://codeforces.com/gym/106554/problem/M
#
# Submissions ~> https://codeforces.com/gym/106554/submission/379236147 By huanhuanonly
#
# @b Binary-search
#
# ----June 17, 2026 [19h:45m:21s]----

n, m, k = map(int, input().split())
v = list(map(int, input().split()))

v.sort()

def check(mid):
    last, maxr, cnt = -1, -1, 0

    for l, r in map(lambda i: (i - mid, i + mid), v):

        if l <= last + 1:
            maxr = r
        else:
            if maxr + 1 < l:
                return False

            last = maxr
            cnt += 1

            maxr = r

            if cnt == m:
                break

    return last >= k or cnt < m and maxr >= k

l, r = -1, 10 ** 12

while r - l > 1:
    mid = l + r >> 1

    if check(mid):
        r = mid
    else:
        l = mid

print(r)