# AtCoder Beginner Contest 471
#
# => E - Sum of Square of Sum ( @c 450 )
#
# -> https://atcoder.jp/contests/abc471/tasks/abc471_e
#
# Submissions ~> https://atcoder.jp/contests/abc471/submissions/78446887 By huanhuanonly
#
# @b Combinatorics
#
# ----August 16, 2026 [01h:52m:45s]----

import math

n, k = map(int, input().split())
v = list(map(int, input().split()))

mod = 998244353

ans = 0
sum = sum(v)

if k >= 2:
    cnt = math.comb(n - 2, k - 2) % mod
    for i in v:
        ans += i * (sum - i) * cnt % mod

cnt = math.comb(n - 1, k - 1) % mod
for i in v:
    ans += i * i * cnt % mod

print(ans % mod)