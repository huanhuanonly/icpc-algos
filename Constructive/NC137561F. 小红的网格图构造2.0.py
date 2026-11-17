# 牛客周赛 Round 153
#
# => F-小红的网格图构造2.0 ( @c 1400 )
#
# -> https://ac.nowcoder.com/acm/contest/137561/F
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84095857 By huanhuanonly
#
# @b Constructive
#
# ----July 19, 2026 [20h:43m:33s]----

n, m, k = map(int, input().split())

if n == 1 or m == 1:
    print('Yes')
    for i in range(n):
        for j in range(m):
            print('1' if k > 0 else '0', end='')
            k -= 1
        print()
else:
    zero, one = '0', '1'

    if k > n * m - k:
        k = n * m - k
        zero, one = '1', '0'

    s = [[one if i & 1 and j & 1 else zero for j in range(m)] for i in range(n)]

    for i in s:
        k -= i.count(one)

    if (n + 1) // 2 * m >= (m + 1) // 2 * n:
        for i in range(0, n, 2):
            for j in range(m):
                if k > 0:
                    s[i][j] = one
                    k -= 1
    else:
        for j in range(0, m, 2):
            for i in range(n):
                if k > 0:
                    s[i][j] = one
                    k -= 1

    if k == 0:
        print('Yes')

        for i in s:
            print(*i, sep='')
    else:
        print('No')