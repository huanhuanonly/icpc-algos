# 牛客周赛 Round 163
#
# => E-小月的门 ( @c 1500 )
#
# -> https://ac.nowcoder.com/acm/contest/140737/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84823473 By huanhuanonly
#
# @b Geometry
#
# ----September 27, 2026 [23h:18m:38s]----

n = int(input())
u1, v1, u2, v2 = map(int, input().split())

def cross(x1, y1, x2, y2, mx = 0, my = 0):
    return (x1 - mx) * (y2 - my) - (x2 - mx) * (y1 - my)

def f(x, y):
    c = cross(u2, v2, x, y, u1, v1)

    if c == 0:
        return 0
    elif c > 0:
        return +1
    else:
        return -1

def intersects(x1, y1, x2, y2):
    return (cross(u2, v2, x1, y1, u1, v1) * cross(u2, v2, x2, y2, u1, v1) < 0
        and cross(x2, y2, u1, v1, x1, y1) * cross(x2, y2, u2, v2, x1, y1) < 0)

diff = 0

for _ in range(n):
    a, b, c, d = map(int, input().split())
    if intersects(a, b, c, d):
        diff += (f(c, d) - f(a, b)) // 2

print(diff)