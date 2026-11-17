# 牛客周赛 Round 153
#
# => E-小红的分割线 ( @c 900 )
#
# -> https://ac.nowcoder.com/acm/contest/137561/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84091300 By huanhuanonly
#
# @b Geometry
#
# ----July 19, 2026 [19h:59m:52s]----

def cross(p0, pm, p1):
    return (p0[0] - pm[0]) * (p1[1] - pm[1]) - (p0[1] - pm[1]) * (p1[0] - pm[0])

n = int(input())
v = [tuple(map(int, input().split())) for _ in range(n)]

ans = 0

for i in range(n):
    for j in range(i + 1, n):
        cnt = [0] * 2
        for k in range(n):
            if k == i or i == j:
                continue

            prod = cross(v[i], v[j], v[k])

            if prod > 0:
                cnt[0] += 1
            elif prod < 0:
                cnt[1] += 1

        if cnt[0] == cnt[1]:
            ans += 1

print(ans)