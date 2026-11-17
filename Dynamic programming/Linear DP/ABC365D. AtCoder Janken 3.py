# Toyota Programming Contest 2024#8（AtCoder Beginner Contest 365）
#
# => D - AtCoder Janken 3 ( @c 400 )
#
# -> https://atcoder.jp/contests/abc365/tasks/abc365_d
#
# Submissions ~> https://atcoder.jp/contests/abc365/submissions/76335131 By huanhuanonly
#
# @b Linear-DP
#
# ----June 02, 2026 [00h:28m:11s]----

n = int(input())
s = input()

map = {' ':' ', 'R':'P', 'P':'S', 'S':'R'}

s = ' ' + s
dp = [[0, 0] for i in range(n + 1)]

for i in range(1, n + 1):
    if s[i - 1] != s[i]:
        dp[i][0] = max(dp[i][0], dp[i - 1][0])
    if s[i - 1] != map[s[i]]:
        dp[i][1] = max(dp[i][1], dp[i - 1][0] + 1)
    if map[s[i - 1]] != s[i]:
        dp[i][0] = max(dp[i][0], dp[i - 1][1])
    if map[s[i - 1]] != map[s[i]]:
        dp[i][1] = max(dp[i][1], dp[i - 1][1] + 1)


print(max(dp[-1]))