# CodeQUEEN 2026 -qual- (AtCoder Beginner Contest 462)
#
# => E - Alternating Costs ( @c 450 )
#
# -> https://atcoder.jp/contests/abc462/tasks/abc462_e
#
# Submissions ~> https://atcoder.jp/contests/abc462/submissions/76700659 By huanhuanonly
#
# @b Classification-discussion
#
# ----June 15, 2026 [11h:39m:43s]----

for _ in range(int(input())):
    a, b, x, y = map(int, input().split())

    if x == y == 0:
        print('0')
        continue

    x, y = abs(x), abs(y)

    ans = 10 ** 19

    mn = min(x, y)
    diff = abs(x - y)

    if diff == 0:
        ans = min(ans, mn * 2 * min(a, b))
    elif x > y:
        ans = min(ans, mn * 2 * a + min(diff // 2 * (a + b) + diff % 2 * a, (diff - 1) * a * 2 + a + (diff % 2 == 0) * a, diff * b * 2 + (diff % 2) * b))
        ans = min(ans, mn * 2 * b + min(diff // 2 * (a + b) + diff % 2 * a, (diff - 1) * a * 2 + a + (diff % 2 == 0) * a, diff * b * 2 + (diff % 2) * b))
    else:
        ans = min(ans, mn * 2 * a + min(diff // 2 * (b + a) + diff % 2 * b, (diff - 1) * b * 2 + b + (diff % 2 == 0) * b, diff * a * 2 + (diff % 2) * a))
        ans = min(ans, mn * 2 * b + min(diff // 2 * (b + a) + diff % 2 * b, (diff - 1) * b * 2 + b + (diff % 2 == 0) * b, diff * a * 2 + (diff % 2) * a))

    print(ans)