# Next DP Contest
#
# => A - Polyomino ( @c 2 )
#
# -> https://atcoder.jp/contests/ndpc/tasks/ndpc2026_a
#
# Submissions ~> https://atcoder.jp/contests/ndpc/submissions/78551947 By huanhuanonly
#
# @b Linear-DP
#
# ----August 21, 2026 [01h:58m:49s]----

n = int(input())
dp = [[0, 0, 0] for _ in range(n + 1)]

dp[0][0] = 1

for i in range(1, n + 1):
    dp[i][0] = sum(dp[i - 1])
    dp[i][1] = dp[i - 1][2]
    dp[i][2] = dp[i - 1][1]

    if i >= 2:
        dp[i][0] += dp[i - 2][0]
        dp[i][1] += dp[i - 2][0]
        dp[i][2] += dp[i - 2][0]

print(dp[-1][0])