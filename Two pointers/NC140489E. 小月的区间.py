# 牛客周赛 Round 162
#
# => E-小月的区间 ( @c 1400 )
#
# -> https://ac.nowcoder.com/acm/contest/140489/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84785337 By huanhuanonly
#
# @b Two-pointers
#
# ----September 22, 2026 [22h:54m:13s]----

n = int(input())
v = list(map(int, input().split()))

vl, vr = [False] * n, [False] * n

mn, mx = n + 1, 0

for i in range(n):
    if v[i] > mx:
        mx = v[i]
        vl[i] = True

for i in range(n - 1, -1, -1):
    if v[i] < mn:
        mn = v[i]
        vr[i] = True

cnt = 0

cl, cr, r = 0, 0, 0

for l in range(n):
    while r < n and (not cl or not cr):
        cl += vl[r]
        cr += vr[r]
        r += 1

    if cl and cr:
        cnt += n - r + 1

    cl -= vl[l]
    cr -= vr[l]

print(cnt)