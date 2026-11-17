# => P16821 [蓝桥杯 2026 国 Python B] 小球消除 ( @c 普及+/提高 )
#
# -> https://www.luogu.com.cn/problem/P16821
#
# Submissions ~> https://www.luogu.com.cn/record/281262579 By huanhuanonly
#
# @b Interval-DP
#
# ----June 09, 2026 [00h:08m:39s]----

for _ in range(int(input())):
    n, c = map(int, input().split())
    v = list(map(int, input().split()))

    dp = [[0] * n for i in range(n)]

    for l in range(n):
        dp[l][l] = 2

    for l in range(n - 1):
        dp[l][l + 1] = 1

    for k in range(3, n + 1):
        for l in range(n - k + 1):
            r = l + k - 1

            dp[l][r] = dp[l + 1][r - 1] + 1

            for mid in range(l, r):
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r])

            if v[l] == v[r]:
                for mid in range(l + 1, r):
                    dp[l][r] = min(dp[l][r], dp[l + 1][mid - 1] + dp[mid + 1][r - 1])

    print(dp[0][-1])