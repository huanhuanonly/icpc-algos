# 第十一届中国大学生程序设计竞赛网络预选赛（CCPC Online 2025）
#
# => A. Counting Lattice Squares 2
#
# -> https://qoj.ac/contest/2534/problem/14547
#
# Submissions ~> https://qoj.ac/submission/2969095 By huanhuanonly
#
# @b Geometry
# @b 2D-Difference-array
#
# ----September 16, 2026 [01h:08m:27s]----

n, m = map(lambda i: int(i) + 1, input().split())

v = [[0] * (m + 1) for _ in range(n + 1)]

for x in range(min(n, m)):
    for y in range(1, min(n, m) - x):
        def add(i, j):
            i2 = n - x - y + i
            j2 = m - x - y + j

            v[i][j] += 1
            v[i][j2] -= 1
            v[i2][j] -= 1
            v[i2][j2] += 1

        add(x, 0)
        add(0, y)
        add(y, y + x)
        add(x + y, x)

for i in range(n + 1):
    v[i][-1] = 0

for j in range(m + 1):
    v[-1][j] = 0

for i in range(n):
    for j in range(m):
        v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1]
        print(v[i][j], end=' \n'[j == m - 1])
