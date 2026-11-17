# AtCoder Beginner Contest 467
#
# => E - Adjacent Sums (hard) ( @c 450 )
#
# -> https://atcoder.jp/contests/abc467/tasks/abc467_e
#
# Submissions ~> https://atcoder.jp/contests/abc467/submissions/77706184 By huanhuanonly
#
# @b Number-theory ( @a modular-arithmetic )
#
# ----July 21, 2026 [00h:07m:35s]----

import collections

n, m = map(int, input().split())
a, b = (list(map(int, input().split())) for _ in range(2))

c = [0] * n

for i in range(1, n):
    c[i] = (b[i - 1] - (a[i - 1] + c[i - 1] + a[i])) % m

d = collections.Counter()

for i in range(1, n):
    if i & 1:
        d[c[i] + 1] += m
    else:
        d[m - c[i]] -= m

ans, sum = (sum(c), ) * 2

for key, value in sorted(d.items()):
    sum += value
    ans = min(ans, sum + key * (n & 1))

print(ans)