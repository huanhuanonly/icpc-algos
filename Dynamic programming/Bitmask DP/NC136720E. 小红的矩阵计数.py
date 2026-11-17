# 牛客周赛 Round 149
#
# => E-小红的矩阵计数 ( @c 1400 )
#
# -> https://ac.nowcoder.com/acm/contest/136720/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83899924 By huanhuanonly
#
# @b Bitmask-DP
#
# ----June 22, 2026 [09h:32m:50s]----

def eq(c0, c1):
    return c0 == c1 or c0 == '?'

n = int(input())
s = [input(), input()]

# 00, 01, 10, 11
dp = [[0, 0, 0, 0] for _ in range(n)]

dp[0][0] = eq(s[0][0], '0') and eq(s[1][0], '0')
dp[0][1] = eq(s[0][0], '0') and eq(s[1][0], '1')
dp[0][2] = eq(s[0][0], '1') and eq(s[1][0], '0')
dp[0][3] = eq(s[0][0], '1') and eq(s[1][0], '1')

mod = 998244353

for i in range(1, n):
    if eq(s[0][i], '0') and eq(s[1][i], '0'):
        dp[i][0] = (sum(dp[i - 1]) - dp[i - 1][0]) % mod
    if eq(s[0][i], '0') and eq(s[1][i], '1'):
        dp[i][1] = sum(dp[i - 1]) % mod
    if eq(s[0][i], '1') and eq(s[1][i], '0'):
        dp[i][2] = sum(dp[i - 1]) % mod
    if eq(s[0][i], '1') and eq(s[1][i], '1'):
        dp[i][3] = (sum(dp[i - 1]) - dp[i - 1][3]) % mod

print(sum(dp[-1]) % mod)