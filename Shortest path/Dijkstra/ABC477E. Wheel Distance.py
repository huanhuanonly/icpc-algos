# UNICORNProgramming Contest2026(AtCoder Beginner Contest 477)
#
# => E - Wheel Distance ( @c 450 )
#
# -> https://atcoder.jp/contests/abc477/tasks/abc477_e
#
# Submissions ~> https://atcoder.jp/contests/abc477/submissions/79622921 By huanhuanonly
#
# @b Dijkstra
#
# ----September 29, 2026 [18h:21m:38s]----

n, q = map(int, input().split())

a = list(map(int, input().split()))
b = list(map(int, input().split()))

a.append(0)
b.append(0)

from heapq import *

que = [(b[i], i) for i in range(n)]
heapify(que)

vis = [False] * n

while que:
    dis, u = heappop(que)

    if vis[u]:
        continue

    vis[u] = True

    v = (u - 1) % n
    if b[u] + a[v] < b[v]:
        b[v] = b[u] + a[v]
        heappush(que, (b[v], v))

    v = (u + 1) % n
    if b[u] + a[u] < b[v]:
        b[v] = b[u] + a[u]
        heappush(que, (b[v], v))

for i in range(n - 1, -1, -1):
    a[i] += a[i + 1]

for _ in range(q):
    s, t = map(lambda i: int(i) - 1, input().split())
    if t == n:
        print(b[s])
    else:
        print(min(b[s] + b[t], a[s] - a[t], a[t] + a[0] - a[s]))