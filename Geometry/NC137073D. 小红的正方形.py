# 牛客周赛 Round 150
#
# => D-小红的正方形 ( @c 1500 )
#
# -> https://ac.nowcoder.com/acm/contest/137073/D
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83988761 By huanhuanonly
#
# @b Geometry
#
# ----July 10, 2026 [17h:04m:05s]----

from bisect import *

a = list(map(int, input().split()))
b = list(map(int, input().split()))

a[0], a[1], a[2], a[3] = min(a[0], a[2]), min(a[1], a[3]), max(a[0], a[2]), max(a[1], a[3])
b[0], b[1], b[2], b[3] = min(b[0], b[2]), min(b[1], b[3]), max(b[0], b[2]), max(b[1], b[3])

st = sorted(set(a) | set(b))

a = list(map(lambda i: bisect_left(st, i), a))
b = list(map(lambda i: bisect_left(st, i), b))

mpa = [[0] * len(st) for _ in range(len(st))]
mpb = [[0] * len(st) for _ in range(len(st))]

for i in range(a[0], a[2] + 1):
    mpa[i][a[1]] |= 1
    mpa[i][a[3]] |= 1

for j in range(a[1], a[3] + 1):
    mpa[a[0]][j] |= 2
    mpa[a[2]][j] |= 2

for i in range(b[0], b[2] + 1):
    mpb[i][b[1]] |= 1
    mpb[i][b[3]] |= 1

for j in range(b[1], b[3] + 1):
    mpb[b[0]][j] |= 2
    mpb[b[2]][j] |= 2

cnt = 0
flag = False

for i in range(len(st)):
    for j in range(len(st)):
        if mpa[i][j] and mpb[i][j]:
            if mpa[i][j] != mpb[i][j] or mpa[i][j] == mpb[i][j] == 3:
                cnt += 1
                if mpa[i][j] == 3 or mpb[i][j] == 3:
                    flag = True
            elif mpa[i][j] == mpb[i][j]:
                cnt += 5

if flag and cnt > 1:
    print('inf')
else:
    print(cnt if cnt <= 4 and a != b else 'inf')