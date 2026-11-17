# CodeQUEEN 2026 -qual- (AtCoder Beginner Contest 462)
#
# => F - More ABC ( @c 500 )
#
# -> https://atcoder.jp/contests/abc462/tasks/abc462_f
#
# Submissions ~> https://atcoder.jp/contests/abc462/submissions/76713431 By huanhuanonly
#
# @b Linear-DP
#
# ----June 15, 2026 [21h:20m:38s]----

def cost(s: str, t: str):
    cnt = 0
    for i, j in zip(s, t):
        cnt += i != j
    return cnt

for _ in range(int(input())):
    s = ' ' + input()
    k = int(input())

    vis = [False] * len(s)

    for i in range(3, len(s)):
        if s[i - 2] == 'A' and s[i - 1] == 'B' and s[i] == 'C':
            vis[i - 2] = vis[i - 1] = vis[i] = True

    inf = 10 ** 9

    dp = [[inf] * (k + 1) for _ in range(len(s))]

    for i in dp:
        i[0] = 0

    for j in range(1, k + 1):
        for i in range(3, len(dp)):
            if vis[i] and s[i] == 'C':
                dp[i][j] = dp[i - 3][j]
            else:
                dp[i][j] = dp[i - 1][j]

            dp[i][j] = min(dp[i][j], dp[i - 3][j - (not vis[i - 2])] + cost(s[i - 2 : i + 1], 'ABC'))

    print(dp[-1][-1] if dp[-1][-1] != inf else '-1')