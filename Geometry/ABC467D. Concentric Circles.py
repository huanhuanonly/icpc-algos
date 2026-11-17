# AtCoder Beginner Contest 467
#
# => D - Concentric Circles ( @c 425 )
#
# -> https://atcoder.jp/contests/abc467/tasks/abc467_d
#
# Submissions ~> https://atcoder.jp/contests/abc467/submissions/77703384 By huanhuanonly
#
# @b Geometry
#
# ----July 20, 2026 [21h:15m:43s]----

def sub(p0, p1):
    return (p0[0] - p1[0], p0[1] - p1[1])

def mid(p0, p1):
    return ((p0[0] + p1[0]) / 2, (p0[1] + p1[1]) / 2)

def dot(p0, p1):
    return p0[0] * p1[0] + p0[1] * p1[1]

def cross(p0, p1):
    return p0[0] * p1[1] - p0[1] * p1[0]

for _ in range(int(input())):
    a, b, c, d = zip(*[map(int, input().split())] * 2)
    print('No' if cross(sub(b, a), sub(d, c)) == 0 and dot(sub(mid(a, b), mid(c, d)), sub(d, c)) != 0 else 'Yes')