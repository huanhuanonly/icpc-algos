# AtCoder Beginner Contest 478
#
# => D - Range Set Insertion Query ( @c 400 )
#
# -> https://atcoder.jp/contests/abc478/tasks/abc478_d
#
# Submissions ~> https://atcoder.jp/contests/abc478/submissions/80040683 By huanhuanonly
#
# @b Difference-array
#
# ----October 14, 2026 [20h:01m:40s]----

n, q = map(int, input().split())
st = [[] for _ in range(n + 2)]

for _ in range(q):
    l, r, x = map(int, input().split())
    st[l].append(x)
    st[r + 1].append(-x)

from collections import Counter
cnt = Counter()

ans = []

for i in range(1, n + 1):
    for x in st[i]:
        if x > 0:
            cnt[x] += 1
        else:
            cnt[-x] -= 1

            if cnt[-x] == 0:
                del cnt[-x]

    ans.append(len(cnt))

print(*ans)