# 牛客周赛 Round 153
#
# => G-小红的网格图构造1.0 ( @c 1800 )
#
# -> https://ac.nowcoder.com/acm/contest/137561/G
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84100340 By huanhuanonly
#
# @b Constructive
#
# ----July 19, 2026 [23h:59m:37s]----

n, m, k = map(int, input().split())

if n == 1 or m == 1:
    s = [['0' for _ in range(m)] for _ in range(n)]

    for i in range(0, n, 2):
        for j in range(0, m, 2):
            if k > 0:
                s[i][j] = '1'
                k -= 1

    if k == 0:
        print('Yes')
        for i in s:
            print(*i, sep='')
    else:
        print('No')
else:
    s = [['1' if i & 1 and j & 1 else '0' for j in range(m)] for i in range(n)]

    k -= (n // 2) * (m // 2)

    if k > 0:
        for i in range(n):
            for j in range(m):
                if k > 0 and (i + j & 1) == 0 and s[i][j] == '0':
                    s[i][j] = '1'
                    k -= 1
    else:
        for i in range(1, n, 2):
            for j in range(2, m - 1, 2):
                if k < 0:
                    s[i][j] = '1'
                    k += 1

        for i in range(2, n - 1, 2):
            if k < 0:
                s[i][1] = '1'
                k += 1

    if k == 0:
        print('Yes')
        for i in s:
            print(*i, sep='')
    else:
        print('No')