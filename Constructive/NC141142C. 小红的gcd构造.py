# 牛客周赛 Round 164
#
# => C-小红的gcd构造 ( @c 1100 )
#
# -> https://ac.nowcoder.com/acm/contest/141142/C
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84877602 By huanhuanonly
#
# @b Constructive
# @b Number-theory ( @a greatest-common-divisor | @a prime-factorization )
#
# ----October 05, 2026 [02h:08m:42s]----

from collections import Counter

for _ in range(int(input())):
    x, y = map(int, input().split())
    cnt = Counter()

    i = 2
    while i <= x / i:
        while x % i == 0:
            x //= i
            cnt[i] += 1
        i += 1

    i = 2
    while i <= y / i:
        while y % i == 0:
            y //= i
            cnt[i] += 1
        i += 1

    if x > 1:
        cnt[x] += 1
    if y > 1:
        cnt[y] += 1

    a, b = 1, 1

    for key, value in cnt.items():
        a *= key ** (value // 2)
        b *= key ** ((value + 1) // 2)

    print(a, b)