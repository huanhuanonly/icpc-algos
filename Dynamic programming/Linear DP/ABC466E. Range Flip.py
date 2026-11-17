# AtCoder Beginner Contest 466
#
# => E - Range Flip ( @c 450 )
#
# -> https://atcoder.jp/contests/abc466/tasks/abc466_e
#
# Submissions ~> https://atcoder.jp/contests/abc466/submissions/77396649 By huanhuanonly
#
# @b Linear-DP and @b Prefix-sum
#
# ----July 11, 2026 [21h:48m:33s]----

n, k = map(int, input().split())

s = 0
d = [0] * (n + 1)

for i in range(1, n + 1):
    a, b = map(int, input().split())
    s += a
    d[i] = d[i - 1] + b - a

dp = [[0] * (k + 1) for _ in range(n + 1)]

for j in range(1, k + 1):
    mx = 0
    for i in range(1, n + 1):
        mx = max(mx, dp[i][j - 1] - d[i])
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1], d[i] + mx)

print(s + dp[-1][-1])