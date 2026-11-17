# 牛客周赛 Round 151
#
# => F-解方程 ( @c 1700 )
#
# -> https://ac.nowcoder.com/acm/contest/137267/F
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83967326 By huanhuanonly
#
# @b Number-theory ( @a divisor | @a greatest-common-divisor )
# @b Combinatorics
# @b Offline
#
# ----July 06, 2026 [02h:05m:51s]----

import math

n = int(input())
v = map(int, input().split())

N = 2 * 10 ** 5 + 1
mod = 10 ** 9 + 7

cnt = [0] * N
fact = [1] * N

for i in range(1, N):
    fact[i] = fact[i - 1] * i % mod

def C(n, k):
    return fact[n] * pow(fact[n - k] * fact[k] % mod, mod - 2, mod) % mod

for x in v:
    sq = int(math.sqrt(x))

    for i in range(1, sq + 1):
        if x % i == 0:
            cnt[i] += 1
            cnt[x // i] += 1

    if sq ** 2 == x:
        cnt[sq] -= 1

maxdiv = [0] * (n + 1)

for i, x in enumerate(cnt):
    maxdiv[x] = max(maxdiv[x], i)

ans = [0] * (n + 1)

cmaxdiv = 0

for i in range(n, -1, -1):
    cmaxdiv = max(cmaxdiv, maxdiv[i])
    ans[i] = C(cnt[cmaxdiv], i)

for _ in range(int(input())):
    k = int(input())
    print(ans[k])