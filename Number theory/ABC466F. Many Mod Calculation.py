# AtCoder Beginner Contest 466
#
# => F - Many Mod Calculation ( @c 500 )
#
# -> https://atcoder.jp/contests/abc466/tasks/abc466_f
#
# Submissions ~> https://atcoder.jp/contests/abc466/submissions/77454182 By huanhuanonly
#
# @b Number-theory ( @a modulus-elimination )
# @b Memoized-search
# @b Binary-search
#
# ----July 13, 2026 [10h:53m:28s]----

import sys
sys.setrecursionlimit(2 * 10 ** 5)

from bisect import *

for _ in range(int(input())):
    n, x = map(int, input().split())
    v = [x + 1]

    if x == 1:
        if min(map(int, input().split())) == 1:
            print('1')
        else:
            print('0')
        continue

    for i in map(int, input().split()):
        if i < v[-1]:
            v.append(i)

    if v[-1] == 1:
        print(x)
        continue

    if len(v) == 1:
        print('0')
        continue

    ans = {}

    def f(x: int) -> int:
        i = bisect_left(v, -x, key=lambda i: -i)

        if i == len(v):
            return 0
        elif x in ans:
            return ans[x]
        elif x == 0:
            return 0
        elif i == len(v) - 1:
            return x // v[i]
        elif x < v[i]:
            ans[x] = f(x)
        else:
            ans[x] = x // v[i] * (f(v[i] - 1) + 1) + f(x % v[i])

        return ans[x]

    print(f(x))