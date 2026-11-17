# 牛客周赛 Round 164
#
# => E-小红的排列构造 ( @c 1500 )
#
# -> https://ac.nowcoder.com/acm/contest/141142/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84877639 By huanhuanonly
#
# @b Constructive
#
# ----October 05, 2026 [03h:35m:50s]----

n, k = map(int, input().split())

if k > (n + 1) // 2:
    print('No')
else:
    print('Yes')

    a, b = [], []

    for i in range(k * 2 - 1, 0, -2):
        a.append(i)

    for i in range(k * 2, 0, -2):
        b.append(i)

    b.reverse()
    a += b
    a = list(map(lambda i: n - len(a) + i, a))

    if len(a) > n:
        a.remove(0)

    print(*[i for i in range(1, n - len(a) + 1)] + a)