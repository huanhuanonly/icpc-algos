# AtCoder Beginner Contest 460
#
# => E - x + y ≡ x + y ( @c 450 )
#
# -> https://atcoder.jp/contests/abc460/tasks/abc460_e
#
# Submissions ~> https://atcoder.jp/contests/abc460/submissions/76355516 By huanhuanonly
#
# @b Number-theory ( @a modular-arithmetic )
#
# ----June 03, 2026 [00h:31m:11s]----

import math

for _ in range(int(input())):
    n, m = map(int, input().split())

    cnt = 0

    for dc in range(1, 19 + 1):
        c = 10 ** dc - 1

        d = m // math.gcd(c, m)

        cnt += n // d * (min(c, n) - (10 ** (dc - 1) - 1))

        if c >= n:
            break

    print(cnt % 998244353)