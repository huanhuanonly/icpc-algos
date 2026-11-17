# 牛客周赛 Round 157
#
# => E-小月的清单 ( @c 1000 )
#
# -> https://ac.nowcoder.com/acm/contest/139206/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84523677 By huanhuanonly
#
# @b Two-heaps
# @b Prefix-sum
# @b Offline
#
# ----August 17, 2026 [00h:10m:32s]----

n, q = map(int, input().split())
v = list(map(int, input().split()))
s = input()

pre = [v[i] if s[i] == '+' else -v[i] for i in range(n)]

for i in range(1, n):
    pre[i] += pre[i - 1]

from heapq import *
queadd, quedel = pre.copy(), []
heapify(queadd)

ans = [False] * (n + 1)

ans[-1] = queadd[0] >= 0

for i in range(n):
    if s[i] == '+':
        ans[i] = queadd[0] - v[i] * 2 >= 0
    else:
        ans[i] = queadd[0] + v[i] * 2 >= 0

    if pre[i] < 0:
        break

    heappush(quedel, pre[i])

    while queadd and quedel and queadd[0] == quedel[0]:
        heappop(queadd)
        heappop(quedel)

ans = list(map(lambda i: 'YES' if i else 'NO', ans))

for _ in range(q):
    p, c = input().split()
    p = int(p) - 1

    if s[p] == c:
        print(ans[-1])
    else:
        print(ans[p])